#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  motorA,          flipperLift,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     rightMotor,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     leftMotor,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     sweep,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     lift,          tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C1_1,    grabber1,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    grabber2,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    dumper,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    stickcontrol,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)

task main()
{
servo[grabber1]=45;
servo[grabber2]=182;
sleep(1000);
while(true){
servo[grabber1]=5;
servo[grabber2]=222;
}
}
