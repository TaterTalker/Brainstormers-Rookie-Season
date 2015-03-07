#include "hitechnic-gyro.h"

task getHead () {
	float delTime = 0;
	float prevHeading = 0;
	float curRate = 0;
	tHTGYRO gyroSensor;
  initSensor(&gyroSensor, msensor_S3_4);
	sensorCalibrate(&gyroSensor);
  float currHeading = 0;

  while (true) {
  	readSensor(&gyroSensor);
    time1[T1] = 0;
    curRate = gyroSensor.rotation*2.36842105
    nxtDisplayBigTextLine(1, "%d", currHeading);
    if (abs(curRate) > 3) {
      prevHeading = currHeading;
      currHeading = prevHeading + curRate * delTime;
      if (currHeading > 360) currHeading -= 360;
      else if (currHeading < 0) currHeading += 360;
    }
    wait1Msec(5);
    delTime = ((float)time1[T1]) / 1000;
    //delTime /= 1000;
  }
}
void gyroturn(){
}

task main(){
	StartTask(getHead);
  sleep(500);
}
