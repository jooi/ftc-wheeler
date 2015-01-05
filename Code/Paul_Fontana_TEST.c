#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)

#pragma config(Sensor, S1,     ,               sensorI2CMuxController)

#pragma config(Sensor, S2,     light,          sensorLightActive)

#pragma config(Sensor, S3,     sonar,          sensorSONAR)

#pragma config(Sensor, S4,     comp,           sensorI2CHiTechnicCompass)

#pragma config(Motor,  motorA,          legom,         tmotorNXT, PIDControl, encoder)

#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)

#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)

#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, encoder)

#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, reversed)

#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoStandard)

#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)

#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)

#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)

#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)

#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//



/*--------------------------------------------------------------------------------------------------------*\

|*                                                                                                        *|

|*                                    - Tetrix Simple Tank Drive -                                        *|

|*                                          ROBOTC on Tetrix                                              *|

|*                                                                                                        *|

|*  This program allows you to drive a robot via remote control using the ROBOTC Debugger.                *|

|*  This particular method uses "Tank Drive" where each side is controlled individually like a tank.      *|

|*                                                                                                        *|

|*                                        ROBOT CONFIGURATION                                             *|

|*    NOTES:                                                                                              *|

|*                                                                                                        *|

|*    MOTORS & SENSORS:                                                                                   *|

|*    [I/O Port]              [Name]              [Type]              [Description]                       *|

|*    Port D                  motorD              12V                 Right motor                         *|

|*    Port E                  motorE              12V                 Left motor                          *|

\*---------------------------------------------------------------------------------------------------4246-*/



#include "JoystickDriver.c"



task main()

{

  servo[servo1] = 0;

                              nMotorEncoder[legom] = 0;                // reset the Motor Encoder of Motor A

                              nMotorEncoder[motorD] = 0;

                              nMotorEncoder[motorE] = 0;

  while(true)                            // Infinite loop:

  {

    getJoystickSettings(joystick);



    motor[motorD] = joystick.joy1_y2;         // Motor D is assigned a power level equal to the right analog stick's Y-axis reading.

    motor[motorE] = joystick.joy1_y1;         // Motor E is assigned a power level equal to the left analog stick's Y-axis reading.

int son=SensorValue[sonar];

    //int a = ServoValue[servo1];

writeDebugStreamLine("motor value: %d", nMotorEncoder[motorD]);

//writeDebugStreamLine("light value: %d", SensorValue(light));

if(son <= 30)

               {

                              motor[legom]=200;

                              motor[legom]=0;

                              nMotorEncoder[legom] = 0;                // reset the Motor Encoder of Motor A

nMotorEncoderTarget[legom] = 20;        // set the  target for Motor Encoder of Motor A to 360

motor[legom] = 75;                       // motor A is run at a power level of 75





//while(nMotorRunState[AAA] != runStateIdle)  // while Motor A is still running (hasn't reached target yet):

//{

  // do not continue

//}

if(nMotorRunState[legom] == runStateIdle)

               {

motor[legom] = 0;                       // motor A is stopped at a power level of 0

                              nMotorEncoder[legom] = 0;                // reset the Motor Encoder of Motor A

}

  }



  // BUTTONS TO CONTOL SERVO ARM

    // Control arm via shoulder buttons, 5 and 6... 5=up, 6=down



    if(joy1Btn(5))          // If Button 5 is pressed:

    {

// nSyncedMotors

               nMotorEncoder[motorD] = 0;

                              nMotorEncoder[motorE] = 0;

                              while (nMotorEncoder[motorD] <=500)

                                             {

                                             motor[motorD] = 40;

                   motor[motorE] = 40;

                 }

    }



    if(joy1Btn(6))          // If Button 6 is pressed:

    {

   //turn 90 degrees to right

    int curhed = SensorValue(comp);

    int newhed = curhed + 90;

    int fuzzyhedlow = newhed - 1;

    int fuzzyhedhigh = newhed + 1;

    if (newhed > 360 )

    {

               newhed = newhed - 360;



    }

    if (fuzzyhedlow > 360)

    {



    fuzzyhedlow = fuzzyhedlow - 360;

  }

  if (fuzzyhedhigh > 360)

    {



    fuzzyhedhigh = fuzzyhedhigh - 360;

  }

    while (SensorValue(comp) != newhed || SensorValue(comp)!= fuzzyhedlow || SensorValue(comp) != fuzzyhedhigh)

               {

//writeDebugStreamLine("compass value: %d", SensorValue(comp));

                              motor[motorD] = 40;

                              motor[motorE] = -40;

               }

      while (SensorValue(light)<=39)

               {

                              writeDebugStreamLine("light value: %d", SensorValue(light));

               motor[motorD] = -40;

               motor[motorE] = -40;

      }

      servo[servo1] = 225;

      //servo[servo1] = 10;

    }

if(joy1Btn(7))          // If Button 6 is pressed:

    {

      servo[servo1] = 225;       // Lower Servo 1 to position 20.

    }

if(joy1Btn(8))          // If Button 6 is pressed:

    {

      servo[servo1] = 10;       // Lower Servo 1 to position 20.

    }



  }

}
