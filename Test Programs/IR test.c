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

#include "functions.h"
#include "gyroturn.h"
#include "lego-ultrasound.h"
#include "lego-touch.h"

task main()
{
	while(true){
		tHTIRS2 irRight;
		initSensor(&irRight, msensor_S2_4);
		irRight.mode = DSP_1200;
		readSensor(&irRight);
		nxtDisplayTextLine(1, "Ir: %d", irRight.acDirection);
		nxtdisplayTextLine(2, "D:%4d %4d 3%d", irRight.dcDirection, irRight.acDirection, irRight.enhDirection);
		nxtdisplayTextLine(3, "1:%4d %d", irRight.dcValues[0], irRight.acValues[0]);
		nxtdisplayTextLine(4, "2:%4d %4d", irRight.dcValues[1], irRight.acValues[1]);
		nxtdisplayTextLine(5, "3:%4d %4d %3d", irRight.dcValues[2], irRight.acValues[2], irRight.enhStrength);
		nxtdisplayTextLine(6, "4:%4d %4d", irRight.dcValues[3], irRight.acValues[3]);
		nxtdisplayTextLine(7, "5%4d %4d", irRight.dcValues[4], irRight.acValues[4]);
	}
}

//yo
//whats enhStrength