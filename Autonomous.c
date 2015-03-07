#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S3,     HTSMUX2,        sensorI2CCustom)
#pragma config(Sensor, S4,     forward,        sensorSONAR)
#pragma config(Motor,  motorA,          flipperLift,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          nxtB,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          nxtC,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     rightMotor,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     leftMotor,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    grabber1,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    grabber2,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    ballRelease,          tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    stickcontrol,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//Same code like you'res August but it use it's AC values from the Ir sensor to more accuratelier determine position
//Same code like you'res August but it use it's AC values from the Ir sensor to more accuratelier determine position
//Same code like you'res August but it use it's AC values from the Ir sensor to more accuratelier determine position
//Same code like you'res August but it use it's AC values from the Ir sensor to more accuratelier determine position
#include "functions.h"
#include "gyroturn.h"
#include "lego-ultrasound.h"
#include "JoystickDriver.c"
#include "lego-touch.h"

#define touch  msensor_S2_3
#define side msensor_S2_1
//#define forward msensor_S2_2
#define woot msensor_S3_3
int irOffset = 0; //change if needed based or results
int turn;

byte Irangle;
int position;

void dumpUpTop(){ //navigates to tower and drops balls
	playSound(soundBeepBeep); //for debugging
	tHTIRS2 irRight; //here
	tHTIRS2 irLeft;
	initSensor(&irRight, msensor_S2_4);
	initSensor(&irLeft, msensor_S3_2);
	irRight.mode = DSP_1200;
	irLeft.mode = DSP_1200; //to here sets up the sensors, one of them is non-existent but I haven't bothered fixing it
	nMotorEncoder[rightMotor]=0; //resets the encoder
	while(nMotorEncoder[rightMotor]<700){ //tracks for  bit without using ultrasonic to align with bacon for ultra lock
		readSensor(&irRight); //reads sensor
		nxtDisplayTextLine(1, "IR: %d	Ultra: %d", irRight.acDirection, SensorValue(forward)); //displays ir and ultra for debugging
		int right = irRight.acDirection;
		int dif = (4-right)*10; //creates turn where it tries to get to slice 4, multiplies by ten to make more responsive

		motor[leftMotor]=15+dif; //drives motors, homing on beacon
		motor[rightMotor]=15-dif;
	}

	while(SensorValue(forward) > 35 || SensorValue(forward)==0) { //same thing as before, except used ultra sonic to get right range
		if(SensorValue(forward)==255){
			motor[leftMotor]=-20;
			motor[rightMotor]=-20
			continue;
		}
		readSensor(&irRight);
		nxtDisplayTextLine(1, "IR: %d	Ultra: %d", irRight.acDirection, SensorValue(forward));
		int right = irRight.acDirection;
		int dif = (4-right)*10;

		motor[leftMotor]=15+dif;
		motor[rightMotor]=15-dif;
	}
	drive(50, 4); //drives rest of distance, otherwise it turns at end
	stopdrive();
	gyroTurn(3);
	servo[ballRelease]=190; //tightens grip on dumper
	nMotorEncoder[lift]=0; //resets lift encoder
	motor[lift]=0;
	servo[ballRelease] = 190; //tightens grip on dumper
	while(nMotorEncoder[lift]<2900){ //raises lift
		motor[lift]=-100;
		nxtDisplayTextLine(5, "%d", nMotorEncoder[lift]);
	}
	motor[lift]=0;
	servo[ballRelease]=0; //dumps
	sleep(1000); //lets balls roll
	drive(10,0.5); //wiggles to shake balls free if stuck
	drive(-10,0.5);
	sleep(1000); //lets balls roll

	while(nMotorEncoder[lift]>1000){ //lowers lift fast at first for speed -----> btw nick, the way you had would only lower at 25, because 500 is closer to 0 than 1000
		//if you had wanted it nested, the one shooting for 500 should have been outside the other
		motor[lift]=75;
		servo[ballRelease]=190;
	}

	while(nMotorEncoder[lift]>60) { //lowers lift slower at end to avoid lift jams
		motor[lift]=25;
	}

	motor[lift]=0; //stops lift
	servo[ballRelease]=190; // of this
	gyroTurn(-90);
	drive(-100, 25);
	sleep(200);
	gyroTurn(-100);
	time1[T2]=0;
	servo[stickcontrol]= 0;
	sleep(900);
	servo[stickcontrol]=128;

	drive(-100, 48);
	pivot(90);
	servo[stickcontrol]= 255;
	sleep(900);
	servo[stickcontrol]=128; //drives over and hits the kickstand
}


task main(){
	tHTIRS2 irRight; //sets up ir
	tHTIRS2 irLeft;
	initSensor(&irRight, msensor_S2_4);
	initSensor(&irLeft, msensor_S3_2);
	irRight.mode = DSP_1200;
	irLeft.mode = DSP_1200;
	startTask(turnTrack); //starts tracking rotation
	nxtDisplayTextLine(2, "gyro calibrating");
	sleep(4000);
	eraseDisplay();

	while(nNxtButtonPressed!=1&&nNxtButtonPressed!=2){}

	position = nNxtButtonPressed; //sees if the left or right button is pressed to determine position
	playSound(soundBeepBeep);

	//waitForStart();

	if(position==1){ //ramp
		nMotorEncoder[rightMotor]=0;
		while(nMotorEncoder[rightMotor]<8000) { //drives down the ramp
			motor[leftMotor] = 50;
			motor[rightMotor] = 50;
		}
		gyroTurnNoReset(); //resets rotation
		sleep(200);
		currHeading=0;
		while(USreadDist(side)==255){}
		while(USreadDist(side)==0){}
		while(SensorValue(forward)==255){}
		while(SensorValue(forward)==0){}

		servo[grabber1]=45;
		servo[grabber2]=182;
		while(nMotorEncoder[rightMotor]<13000) { //drives till it gets near the tube

			if(nMotorEncoder[rightMotor]%3000<50){ //periodically resets rotation counter to avoid strange readings
				sleep(200);
				currHeading=0;
			}
			turn=(USreadDist(side)-18)*3;
			if(nMotorEncoder[rightMotor]<0) nMotorEncoder[rightMotor]=0;
			if(turn>10) turn=10;
			if(turn<-10) turn=-10;
			motor[leftMotor] = 20 - turn;
			motor[rightMotor] = 20 + turn;
			servo[grabber1]=45;
			servo[grabber2]=182;
		}

		stopdrive(); //stops
		servo[ballRelease]=190; //makes sure the ball release isn't down
		servo[grabber1]=45;
		playSound(soundBeepBeep);
		servo[grabber2]=182; //gets ready to grab the tube
		nMotorEncoder[lift]=0;
		while(nMotorEncoder[lift]<1170){
			motor[lift] = -100; //lifts the lift
		}
		motor[lift] = 0;
		nMotorEncoder[leftMotor]=0;
		drive(20, 8); //goes to the tube
		servo[grabber1]=5;
		servo[grabber2]=222; //grabs the tube
		sleep(700);
		servo[ballRelease] = 0; //dumps
		sleep(2900);//waits for balls to roll
		currHeading=0; // resets gyro
		while(currHeading>-90){ //performs 1 wheel turn to avoid collision with wall
			motor[leftMotor]=20;
		}
		stopdrive(); //stops
		drive(20, 5); // goes forward to avoid ramp
		gyroTurn(-55); //runs toward parking zone
		servo[grabber1]=5; //reaffirms grab
		servo[grabber2]=222;
		servo[ballRelease] = 190; //brings up dumper
		nMotorEncoder[leftMotor]=0;
		while(nMotorEncoder[leftMotor]<14000) { //drives to parking zone
			motor[leftMotor] = 100;
			motor[rightMotor] = 100;
		}
		stopdrive(); //stops

		servo[grabber1]=45; //releases tube
		while(nMotorEncoder[lift] > 540) {
			motor[lift] = 20;
		}
		servo[servo3]=190;

		servo[grabber2]=182;
		sleep(500);
		motor[lift] = 0;
		while(nMotorEncoder[leftMotor]>0) { //goes back toward tubes to reduce driving time
			motor[leftMotor] = -100;
			motor[rightMotor] = -100;
		}
	}




	else{ //box
		time1[T4]=0;
		while(time1[T4]<200){ //repeatedly reads ir to avoid only reading 0
			readSensor(&irRight);
		}
		Irangle = irRight.acDirection; //determines position, 4=3, 3=2, something else=1
		if(Irangle==4&&irRight.enhStrength>45){ //just drives and dumps balls
			dumpUpTop(); //runs dump function
		}

		if (Irangle == 3 && irRight.acValues[1] > 20) { //drives to get straight on and drives to dump balls
			nxtdisplayTextLine(4, "2:%4d %4d", irRight.dcValues[1], irRight.acValues[1]); // sense ac value to determine whether center goal is in position 2 or 3
			drive(100, 35); // moves forward to allow turning
			sleep(200); //waits for motion to stop
			gyroTurn(-80); //turns
			drive(100, 35); //drives to right in front of thin side of center structure
			sleep(200); //waits for motion to stop
			gyroTurn(125); //turns toward structure
			dumpUpTop(); //runs dump function

		}
		if (Irangle == 3 || irangle == 5){
			if (irRight.acValues[1] < 20 || irRight.acValues[2] !=0) {
				nxtdisplayTextLine(4, "2:%4d %4d", irRight.dcValues[1], irRight.acValues[1]);
				nxtdisplayTextLine(4, "3:%4d %4d", irRight.dcValues[2], irRight.acValues[2]);
				//what the heck is this monstrosity? ^ why 2 lines of code, it will just overlap, whoever is programming this is a moron
				//give up while you're behind
				//just tell me what you want me to do
				playSound(soundBeepBeep);

				drive(100, 35); //does forward to allow turning
				sleep(200); //waits for motion to stop
				gyroTurn(-26); //turns in direction to just miss center structure
				drive(100, 60); // drives to right in front of center structure
				sleep(200); //waits for motion to stop
				gyroTurn(125); //turns towards structure
				drive(-20, 10);
				sleep(500); //waits for motion to stop
				dumpUpTop();//runs dump function
			}
		}
	}
}
