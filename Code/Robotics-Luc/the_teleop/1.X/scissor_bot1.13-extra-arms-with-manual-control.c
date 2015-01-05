#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorLightInactive)
#pragma config(Motor,  mtr_S1_C1_1,     left,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     right,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     arm,           tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    sec_arm,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    sec_arm,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    bottle,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//141114 Luc - continue main dev for WS Robot competition
//141115 Luc - using position returned from encoders

#include "JoystickDriver.c"

int dband=30; //deadband
int joy_1y1;
int joy_1y2;
int joy_1x1;
int joy_1x2;
float joyslope=(float)100/128;//the max joy is 128 and the max motor speed is 100
int tophat;//1=down 2=up 0=no where
int currpos=0;//start lift on floor
//int state=0;//lift should start on ground
int armrot[3]={0,50,100};//CURRENTLY FAKE NUMBERS!!!!!! arm rotations for different levels (can be called by 0,1,2 0 being ground and 2 being highest)
int sec_armrot[3]={0,7,180};//rotations for arm at different levels
int min_sec_armrot=0;
int tophat_old=-1;
int maxspeed=80;
int nextpos=0;
int tip_button_old=0;//0=off and 1=on (like what joy buttons normally return)
//int sec_manualoveride=0;//code 0 (no) 1 (yes)
//int bottleopen=0;//state of 1 (open) or 0 (closed)

int transfer_J_To_M(int joy,float slope,int dead) // joy = joy input, dead = dead band, slope = max motor output/max joy input - in this case 100/128
{
	int y;
	if (abs(joy)<dead)
		y=0;
	else
		y=slope*((float)joy-(float)dead*sgn(joy));

	return y;
}

int whatLevelBelow()
{

}

void liftmovement(/*int currpos, int tophat*/){//I shouldn't need to have an input for them because I initialised them at top
	int main_rotateamount=0;
	int sec_rotateamount=0;

	if ( sgn(joy_1y2)==1 && currpos < sizeof(sec_armrot)/sizeof(int) )//is up and isn't on roof
	{
		nextpos=currpos+1;
		motor[arm]=joy_1y2;//setting speed of arm
		servo[sec_arm]=sec_armrot[currpos];
		if (motor[arm]>=armrot[nextpos])//checking if it is bigger or equal to the next pos so it can increment currpos
		{
			currpos=nextpos;
		}
		writeDebugStreamLine("horray (up), %d, %d", motor[arm], servo[sec_arm]);
	}
	else if (sgn(joy_1y2)==-1 && currpos!=0)//is down and isn't on floor
	{
		nextpos=currpos-1;
		motor[arm]=joy_1y2;
		servo[sec_arm]=sec_armrot[currpos];
		if (motor[arm]<=armrot[nextpos])//checking if it is smaller or equal to the next pos so it can decrement currpos
		{
			currpos=nextpos;
		}
		writeDebugStreamLine("horray (down), %d, %d", motor[arm], servo[sec_arm]);
	}
	else//manual control joy is not being used
	{
		motor[arm]=0;

		if (tophat!=tophat_old)
			{
			switch (tophat){
			case 0://if tophat is up
				if (currpos==sizeof(armrot)/4-1){//if on roof then don't go up
				}
				else{
					main_rotateamount=armrot[currpos+1]-armrot[currpos];
					sec_rotateamount=sec_armrot[currpos+1];
					nMotorEncoderTarget[arm]=main_rotateamount;
					motor[arm]=maxspeed;
					servo[sec_arm]=sec_rotateamount;
					servo[bottle]=sec_rotateamount;
					currpos++;
				}
				writeDebugStreamLine("%d", servo[bottle]);
				writeDebugStreamLine("%d", currpos);
				break;
			case 4://if tophat is down
				if (currpos==0)//if on floor then don't go down
				else{
					main_rotateamount=armrot[currpos-1]-armrot[currpos];
					sec_rotateamount=sec_armrot[currpos-1];
					nMotorEncoderTarget[arm]=main_rotateamount;
					motor[arm]=maxspeed;
					servo[sec_arm]=sec_rotateamount;
					servo[bottle]=sec_rotateamount;
					currpos--;
				}
				writeDebugStreamLine("%d", servo[bottle]);
				writeDebugStreamLine("%d", currpos);
				break;
				//default:
				//writeDebugStreamLine("cmon");
			}
		}
	}
}

task main(){
	clearDebugStream();
	while (true)
	{
		getJoystickSettings(joystick);
		joy_1y1=transfer_J_To_M(joystick.joy1_y1, joyslope, dband); //left (front,back)
		joy_1y2=transfer_J_To_M(joystick.joy1_y2, joyslope, dband); //OVERIDE- up down
		joy_1x1=transfer_J_To_M(joystick.joy1_x1, joyslope, dband); //NIU- NOT IN USE
		joy_1x2=transfer_J_To_M(joystick.joy1_x2, joyslope, dband); //
		tophat=joystick.joy1_TopHat;
		//writeDebugStreamLine("%d", tophat);

		liftmovement();
		tophat_old=tophat;
		motor[left] = (joy_1y1 + joy_1x1) / 2;
		motor[right] = (joy_1y1 - joy_1x1) / 2;

		//trying to find the smallest rotation ever made (not including 0)
		for (int ii=0;ii<(sizeof(sec_armrot)/4);ii++)
		{
			//writeDebugStreamLine("%d",ii);
			y=sec_armrot[ii];
			//writeDebugStreamLine("%d", y);
			if (y!=0)
			{
				min_sec_armrot=y;
				writeDebugStreamLine("%d", y);
				break;
			}
		}

		if (tip_button_old!=joy1Btn(1))
		{
			if(servo[bottle]==servo[sec_arm] && joy1Btn(1)==1)//if it is not in ball dropping pos
			{
				if (min_sec_armrot<=servo[bottle]){
					servo[bottle]=45;
					writeDebugStreamLine("open");
				}
			}
			else if(joy1Btn(1)==1)//it's already in ball dropping pos
			{
				servo[bottle]=servo[sec_arm];
				writeDebugStreamLine("close");
			}
		}
		tip_button_old=joy1Btn(1);
	}
}
