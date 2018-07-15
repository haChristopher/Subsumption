
#include "Arduino.h"

#include <Servo.h>
#include <math.h>

// Motor Controls
#define C_NONE      0
#define C_STOP      1
#define C_FORWARD   2
#define C_TURN      3

Servo leftFrontLegServo;
Servo rightFrontLegServo; 
Servo headServo;
Servo leftBackLegServo;  
//Servo rightBackLegServo; 
int pos1, pos2, pos3, pos4, pos5;
double counter;

// last excecuted behavior
char last_winner;

void setup() {

  Serial.begin(9600);
  
  last_winner = C_NONE;
  
  pos1=15;   // bein links vorne
  pos2=125;   // bein rechts vorne
  pos3=60;   // kopf
  pos4 =40;  // bein links hinten
  pos5 =155; // bein rechts hinten

  leftFrontLegServo.attach(11);  
  rightFrontLegServo.attach(10); 
  //headServo.attach(9); 
  leftBackLegServo.attach(6); 
  //rightBackLegServo.attach(5);

  leftFrontLegServo.write(pos1);
  rightFrontLegServo.write(pos2);
  //headServo.write(pos3+angle1);
  leftBackLegServo.write(pos4 -20);
  //rightBackLegServo.write(pos5+angle2);
  
  counter=0;
}


void loop() {  
  if(avoid_wants_to_run){
    //avoid();
    //get_light_readings();
  }
  //move_step_foreward();
  //delay(1);
  turn_step_left();
}

void arbitrate(char command){
    // choose task and inform about winner
    switch(command){
      case C_FORWARD :
        move_step_foreward();
        last_winner = C_FORWARD;
        break;
      case C_TURN :
        last_winner = C_TURN;
        break;
      case C_STOP :
        last_winner = C_STOP;
        break;
    }
}

void get_light_readings(){
    //move_slow_to(headServo, 0);
    //headServo.write(0);
    Serial.println(analogRead(A5));
    delay(1000);
    //headServo.write(160);
    //move_slow_to(headServo, 180);
    Serial.println(analogRead(A5));
    delay(1000);
}


boolean avoid_wants_to_run(){
  return 500 < get_distance();
}

void avoid(){
  while(500 < get_distance()){
    //move_slow_to(leftBackLegServo, 30);
    //move_slow_to(rightBackLegServo, 130);
    turn_step_left();
  }
}

int get_distance(){
  return analogRead(A3);
}

void move_step_foreward(){
  double angle1 = 20*sin(counter);
  double angle2 = 20*cos(counter);
    
  //leftFrontLegServo.write(pos1+angle1);
  //rightFrontLegServo.write(pos2+angle1);
  //headServo.write(pos3+angle1);
  //leftBackLegServo.write(pos4+angle2);
  //rightBackLegServo.write(pos5+angle2);
  counter=counter+0.002;
}

void turn_step_head(){
  double angle1 = 20*sin(counter);
  //headServo.write(pos3+angle1);
  counter=counter+0.002;
}

void turn_step_left(){
   double angle1 = 20*sin(counter);
  double angle2 = 20*cos(counter);
    
  leftFrontLegServo.write(pos1+angle1);
  //rightFrontLegServo.write(pos2+angle1);
  //headServo.write(pos3+angle1);
  //leftBackLegServo.write(pos4+angle2);
  //rightBackLegServo.write(pos5+angle2);
  counter=counter+0.002;
}

void move_slow_to(Servo servo, int to){
    int current_position = servo.read();
    int factor = current_position > to ? -1: 1;
    for (int x = current_position; x != to; x++) {
       servo.write(current_position + (x * factor));
    }
}

void turn_step_right(){
}
