#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Motor,  mtr_S1_C3_2,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Sensor, S2,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S3,     HTSMUX2,        sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "hitechnic-sensormux.h"
#include "lego-ultrasound.h"

#define woot msensor_S3_3

task main(){
	while(true){
		int but=nNxtButtonPressed;
		nxtDisplayBigTextLine(5, "%d", USreadDist(woot);
		nxtDisplayBigTextLine(2, "%d", nMotorEncoder[lift]);
	switch(but){
		case 1: motor[lift]=-50;
		break;
		case 2: motor[lift]=50;
		break;
		default:
		motor[lift]=0;
		break;
	}
}
}
