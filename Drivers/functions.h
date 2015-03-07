#include "hitechnic-sensormux.h"
#include "lego-touch.h"
#include "lego-ultrasound.h"
#include "hitechnic-irseeker-v2.h"


void drive (int power, float inches) {
	nMotorEncoder[rightMotor]=0;
	nMotorEncoder[leftMotor]=0;
	if (power>0){
			while(nMotorEncoder[rightMotor] < 110*inches || nMotorEncoder[leftMotor] < 110*inches){
		motor[rightMotor] = power;
		motor[leftMotor] = power;
	}
	}else{
			while(nMotorEncoder[rightMotor] > -110*inches || nMotorEncoder[leftMotor] > -110*inches){
		motor[rightMotor] = power;
		motor[leftMotor] = power;
	}
	}
	motor[rightMotor] = 0;                       // motor B is stopped at a power level of 0
	motor[leftMotor] = 0;                       // motor C is stopped at a power level of 0
	sleep(20);
}





void pivot (int degrees) {
	nMotorEncoder[rightMotor]=0;
	nMotorEncoder[leftMotor]=0;
	if (degrees>0){
			while(nMotorEncoder[rightMotor] < 21*degrees || nMotorEncoder[leftMotor] > -21*degrees){
		motor[rightMotor] = 50;
		motor[leftMotor] = -50;
	}
	}else{
			while(nMotorEncoder[rightMotor] > 21*degrees || nMotorEncoder[leftMotor] < -21*degrees){
		motor[rightMotor] = -50;
		motor[leftMotor] = 50;
	}
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
	sleep(20);
}
}


void stopdrive(){
	motor[leftMotor]=0;
	motor[rightMotor]=0;
	sleep(10);
}
//multiplexer functions
