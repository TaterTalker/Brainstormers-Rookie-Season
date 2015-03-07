#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S3,     HTSMUX2,        sensorI2CCustom)
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
task main()

{
	nMotorEncoder[flipperLift]=0;
	while(nMotorEncoder[flipperLift]<1440){
		motor[flipperLift]=100; //OHJFAFSADHUIFDDHUIFDAKHFDKLJSHFID --> CHANGE THIS UP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! <-- ASKJFHAKJSDHFK
	}
	motor[flipperLift]=0;
}
