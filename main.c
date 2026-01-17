#include "LedControl.h"
#include <Adafruit_MPU6050.h>
#include <Wire.h>

/*
 Arduino Program (Mega 2560) designed to simulate a game where the player must avoid walls using a gyro sensor (MPU-6050) by moving left and right
 
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 

 */
LedControl lc=LedControl(12,11,10,1);
Adafruit_MPU6050 mpu;

float count_l=0;
int row_l=-1;

float count_r=0;
int row_r=-4;

int gap_l;
int gap_r;

int score =0;
float time_factor =10;

void setup(){
  Wire.begin();
  Serial.begin(115200);

  if(!mpu.begin()){
    Serial.println("Failed to initialize MPU6050");
    while(1);
  }

  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,1);
  /* and clear the display */
  lc.clearDisplay(0);
}

void loop(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  //int x = map(a.acceleration.x, -9.8, 9.8, 0, 7);
  int player_y = map(a.acceleration.y, -9.8, 9.8, 0, 7);

  lc.clearDisplay(0);
  lc.setLed(0,player_y,5,true);
  //Serial.println(x,y);
  if(checkCollision(row_l, row_r, player_y)){
    Serial.println("Game Over...");
    while(1) {
      lc.clearDisplay(0);
    }
  }

  setGap();

  if(count_l >=time_factor){
    count_l =0;
  }
  if(count_r >=time_factor){
    count_r =0;
  }
  count_r++;
  count_l++;
  delay(100);
}

bool checkCollision(int wall_row_l, int wall_row_r, int player_col){
  if(wall_row_l == 5){
    if(player_col < gap_l) {
      return true;
    }
  }

  if(wall_row_r == 5){
    if(player_col > (7-gap_r)) {
      return true;
    }
  }
  return false;
}

void setGap(){
  if(row_l <=-1) gap_l = random(3,6);
  if(row_r <=-1) gap_r = random(3,6);
  //if(count_l ==10)Serial.println(gap);

  leftWall(gap_l);
  rightWall(7-gap_r);
}

void leftWall(int max){
  if(row_l==7) {
    row_l=-1;
    time_factor *=0.75;
    Serial.print("Score: ");
    Serial.println(++score);
  }  
  if(count_l >= time_factor) row_l++;
  for(int i = 0; i < max; i++){
    lc.setLed(0,i,row_l,true);
  }
}

void rightWall(int max){
  if(row_r==7) row_r=-1;
  if(count_r >= time_factor) row_r++;
  for(int j = 7; j > max; j--){
    lc.setLed(0,j,row_r,true);
  }
}
