#pragma config(Sensor, S1,     accel,          sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-accelerometer.h"

task main()
{
	int x;
	int y;
	int z;
	int advanced=true;
	while (true){
		if (advanced){
			HTACreadAllAxes(accel, x, y, z);
			nxtDisplayCenteredBigTextLine(1,"%d", x);
			nxtDisplayCenteredBigTextLine(3,"%d", y);
			nxtDisplayCenteredBigTextLine(6,"%d", z);
		}
		else {
			int sensorVal=SensorValue[accel];
			nxtDisplayCenteredBigTextLine(3,"%d", sensorVal);
		}
	}
}
