#include "hitechnic-gyro.h"
float currHeading = 0;

task turnTrack() {
	float delTime = 0;
	float prevHeading = 0;
	float curRate = 0;
  currHeading = 0;
  tHTGYRO gyroSensor;
  initSensor(&gyroSensor, msensor_S3_4);
  sensorCalibrate(&gyroSensor);
  while(true){

  	readSensor(&gyroSensor);
    time1[T1] = 0;
    curRate = gyroSensor.rotation*2.36842105;
    if (abs(curRate) > 3) {
      prevHeading = currHeading;
      currHeading = prevHeading + curRate * delTime;
    }
    wait1Msec(5);
    delTime = ((float)time1[T1]) / 1000;
    //delTime /= 1000;
  }
    motor[leftMotor]=0;
 	motor[rightMotor]=0;
}

void gyroTurn(int degrees){
  //if(degrees>0)degrees -= 3;
  //else degrees += 3;
  currHeading=0;
  sleep(100);
  while(abs(degrees)>abs(currHeading)){
  	motor[leftMotor]= -15*abs(degrees)/degrees;
  	motor[rightMotor]= 15*abs(degrees)/degrees;
  }
  motor[leftMotor]= 0;
 	motor[rightMotor]= 0;
}


void gyroTurnNoReset(int degrees=1, int speed=15){
  sleep(100);
  while(abs(degrees)<abs(currHeading)){
  	motor[leftMotor]= -speed*abs(degrees-currHeading)/(degrees-currHeading);
  	motor[rightMotor]= speed*abs(degrees-currHeading)/(degrees-currHeading);
  	nxtDisplayTextLine(1, "%d", currHeading);
  }
  motor[leftMotor]= 0;
 	motor[rightMotor]= 0;
}
