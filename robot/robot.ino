#include "Arduino.h"

#include <Servo.h>
#include <math.h>

// Behaviors
#define C_NONE      0
#define C_STOP      1
#define C_FORWARD   2
#define C_REVERSE   3
#define C_TURNLEFT  4
#define C_TURNRIGHT 5

// Check numbers
// Stop - is this a good way to do it ?
#define LEFT_FRONT_STOP  leftFrontLegServo.write(90);
#define RIGHT_FRONT_STOP rightFrontLegServo.write(90);
#define LEFT_BACK_STOP  leftBackLegServo.write(90);
#define RIGHT_BACK_STOP rightBackLegServo.write(90);
#define HEAD_STOP sonarServo.write(90);


Servo leftFrontLegServo;
Servo rightFrontLegServo;
Servo headServo;
Servo leftBackLegServo;
Servo rightBackLegServo;

int pos1, pos2, pos3, pos4, pos5;
double counter;

void print_distance(){
        Serial.print(analogRead(A3));
}


void setup() {
        // initialize digital pin LED_BUILTIN as an output.
        pinMode(LED_BUILTIN, OUTPUT);

        Serial.begin(115200);

        pos1=15; // bein links vorne
        pos2=125; // bein rechts vorne
        pos3=60; // kopf
        pos4 =40; // bein links hinten
        pos5 =140; // bein rechts hinten

        leftFrontLegServo.attach(11);
        rightFrontLegServo.attach(10);
        headServo.attach(9);
        leftBackLegServo.attach(6);
        rightBackLegServo.attach(5);

        counter=0;
}

void loop() {
        double angle1 = 20*sin(counter);
        double angle2 = 20*cos(counter);

        if (analogRead(A3)>250) {
                angle1=0;
                angle2=0;
        }
        leftFrontLegServo.write(pos1+angle1);
        rightFrontLegServo.write(pos2+angle1);
        headServo.write(pos3+angle1);
        leftBackLegServo.write(pos4+angle2);
        rightBackLegServo.write(pos5+angle2);
        print_distance();
        counter=counter+0.002;
}

// Bring all servos back to starting postion
void stop()
{
        LEFT_FRONT_STOP;
        RIGHT_FRONT_STOP;
        LEFT_BACK_STOP;
        RIGHT_BACK_STOP;
        HEAD_STOP;
}
