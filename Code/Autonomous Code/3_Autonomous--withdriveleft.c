#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftdrive,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightdrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     ballgrabber,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    sarm,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    bottle,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    spinner,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    grabber,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"

//TASK: Drive down ramp; put goals in zone

task main()
{
	//waitForStart();
	motor[leftdrive] = 50;   // drive to edge of ramp
	motor[rightdrive] = 50;  // test for corect values
	wait1Msec(1000);

	motor[leftdrive] = 0;
	motor[rightdrive] = 0;
	wait1Msec(1000);

	motor[leftdrive] = 10;  // drive off ramp
	motor[rightdrive] = 10; // test for correct values
	wait1Msec(500);

	motor[leftdrive] = 0;
	motor[rightdrive] = 0;
	wait1Msec(1000);

	motor[leftdrive] = -50;
	motor[rightdrive] = 50;
	wait1Msec(200);

	motor[leftdrive] = 0;
	motor[rightdrive] = 0;
	wait1Msec(1000);

	motor[leftdrive] = 50;
	motor[rightdrive] = 50;
	wait1Msec(1000);

	/*servo[grabber] = 90;
	servoChangeRate[grabber] = 2; // servo moves down, clamps onto goal

	motor[leftdrive] = 0;
	motor[rightdrive] = 0;
	wait1Msec(250);

	motor[leftdrive] = -50; // robot turns to face zone
	motor[rightdrive] = 50; // test for correct values
	wait1Msec(1000);

	motor[leftdrive] = 0;
	motor[rightdrive] = 0;
	wait1Msec(250);

	motor[leftdrive] = 50; // robot drives into zone
	motor[rightdrive]= 50; // test for correct values
	wait1Msec(1000);

	servo[grabber] = 0;
	servoChangeRate[grabber] = 2; // servo moves up, lets go
	                              // test for correct values


*/
}
