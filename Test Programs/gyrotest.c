#pragma config(Sensor, S3,     HTSMUX2,         sensorI2CCustom)
#include "hitechnic-gyro.h"

task main () {
	float delTime = 0;
	float prevHeading = 0;
	float curRate = 0;
	tHTGYRO gyroSensor;
  initSensor(&gyroSensor, msensor_S3_4);
	sensorCalibrate(&gyroSensor);
  float currHeading = 0;
  PlaySound(soundBeepBeep);
  while (true) {
  	readSensor(&gyroSensor);
    time1[T1] = 0;
    curRate = gyroSensor.rotation*2.36842105
    nxtDisplayBigTextLine(1, "%d", currHeading);
    if (abs(curRate) > 3) {
      prevHeading = currHeading;
      currHeading = prevHeading + curRate * delTime;
    }
    wait1Msec(5);
    delTime = ((float)time1[T1]) / 1000;
    //delTime /= 1000;
  }
}
