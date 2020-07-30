#include "inverter.h"
#define FWD  CCW
#define REV  CW
#define NAN  -1

Motor motor1(13, 12, 11);
Motor motor2(8, 9, 10);
Motor motor3(7, 6, 5);
Motor motor4(4, 2, 3);

int t = 1;

enum { up, down, left, right, up_right, down_right, down_left, up_left, rotate_cw, rotate_ccw };

int motor_map[10][4] = {
  {REV, FWD, REV, FWD},
  {FWD, REV, FWD, REV},
  {REV, REV, FWD, FWD},
  {FWD, FWD, REV, REV},
  {NAN, REV, FWD, NAN},
  {FWD, NAN, NAN, REV},
  {NAN, FWD, REV, NAN},
  {REV, NAN, NAN, FWD},
  {REV, REV, REV, REV},
  {FWD, FWD, FWD, FWD}
};

void motor_drive(int mode) {
  
  if(motor_map[mode][0] == NAN) motor1.drive(OFF);
  else motor1.drive(ON, motor_map[mode][0]);
  
  if(motor_map[mode][1] == NAN) motor2.drive(OFF);
  else motor2.drive(ON, motor_map[mode][1]);
  
  if(motor_map[mode][2] == NAN) motor3.drive(OFF);
  else motor3.drive(ON, motor_map[mode][2]);
  
  if(motor_map[mode][3] == NAN) motor4.drive(OFF);
  else motor4.drive(ON, motor_map[mode][3]);
}

void setup() {
  Serial.begin(9600);
  Serial.println("hi");
  motor1.set_speed(60);
  motor2.set_speed(60);
  motor3.set_speed(60);
  motor4.set_speed(60);
  //while(1);
}

const char *str[10] = {
  "up", "down", "left", "right", "up_right", "down_right", "down_left", "up_left", "rotate_cw", "rotate_ccw"
};

void loop() {
  char c = Serial.read();
  if('0' <= c && c <= '9' || c == 's') {
    if(c == 's') Serial.println("STOP");
    else Serial.println(str[c-'0']);
    motor_drive(c == 's' ? NAN : c-'0');
  }
}
