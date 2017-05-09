//Include Library
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

//speed controller
Servo esc;
int throttlePin = A0;

//LCD
LiquidCrystal_I2C lcd(0x3F,20,4);

//MOTOR   
const int rightMotorP = A8;
const int rightMotorN = A9;
const int leftMotorP = A10;
const int leftMotorN = A11;

//Ultrasonic Sensor
const int trig_1 = 2;
const int echo_1 = 3;
const int trig_2 = 4;
const int echo_2 = 5;
const int trig_3 = 6;
const int echo_3 = 7;
const int trig_4 = 8;
const int echo_4 = 9;

//defines variables
long duration_1, duration_2, duration_3, duration_4;
int distance_1, distance_2, distance_3, distance_4;

//Buttons
#define start 52
#define pause 53

void setup() {

  //initialize the position of vacuum speed 
  esc.attach(10); // attached to pin "10" PWM pin
  esc.writeMicroseconds(1000);

  //LCD
  lcd.init(); // initialize the lcd 
  lcd.init();  
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(4,0);
  lcd.print("Hello !");
  lcd.setCursor(0,1);
  lcd.print("Please wait...");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press  Start - ");
  lcd.setCursor(0,1);
  lcd.print("Button");
  
  //MOTOR
  pinMode(rightMotorP, OUTPUT);
  pinMode(rightMotorN, OUTPUT);
  pinMode(leftMotorP, OUTPUT);
  pinMode(leftMotorN, OUTPUT);

  //Button
  pinMode(start, INPUT);
  pinMode(pause, INPUT);

  //Ultrasonic Sensor
  pinMode(trig_1, OUTPUT); 
  pinMode(echo_1, INPUT);
  pinMode(trig_2, OUTPUT); 
  pinMode(echo_2, INPUT);
  pinMode(trig_3, OUTPUT); 
  pinMode(echo_3, INPUT);
  pinMode(trig_4, OUTPUT); 
  pinMode(echo_4, INPUT);

}


void vacuum_start(){
  int throttle = analogRead(throttlePin);
  throttle = map(throttle, 0, 1023, 1000, 2000);
  esc.writeMicroseconds(throttle);
}

    
void loop() {

  //Read Pins
  int readStart = digitalRead(start);
  int readPause = digitalRead(pause);
  
  //Start Button
  if(readStart == HIGH){
    //LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Thank you!!");
    delay(1000);
    lcd.clear();
    
    //Motors
    analogWrite(rightMotorP, 130); 
    analogWrite(rightMotorN, 0);
    analogWrite(leftMotorP, 130); 
    analogWrite(leftMotorN, 0);
    vacuum_start(); //vacuum on when start pressed
  }

  UV1();
  UV2();
  UV3();
  UV4();

  // keep the vacuum fan on all the time. Use throttle pin to increase speed 
  vacuum_start(); 

  //Stop Button
  if(readPause == HIGH){
    //LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Good bye!");
    delay(1000);
    lcd.clear();
    
    //Motors
    analogWrite(rightMotorP, 0); 
    analogWrite(rightMotorN, 0);
    analogWrite(leftMotorP, 0); 
    analogWrite(leftMotorN, 0);
  }    
}

void UV1(){

  //Ultrasonic sensors_1
  digitalWrite(trig_1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_1, LOW);
  
  duration_1= pulseIn(echo_1, HIGH);
  distance_1= duration_1*0.034/2; //speed of sound is known

  //Ultrasonic sensors_1
  if(distance_1 == 7 ){
    //Motors
    analogWrite(rightMotorP, 0); 
    analogWrite(rightMotorN, 130);
    analogWrite(leftMotorP, 0); 
    analogWrite(leftMotorN, 130);
    delay(1000);
    analogWrite(rightMotorP, 130); 
    analogWrite(rightMotorN, 0);
    delay(1500);
    analogWrite(leftMotorP, 0); 
    analogWrite(leftMotorN, 0);
    analogWrite(rightMotorP, 130);
    analogWrite(rightMotorN, 0);
    analogWrite(leftMotorP, 130); 
    analogWrite(leftMotorN, 0);  
  }
}
  
void UV2 (){
  
  //Ultrasonic sensors_2
  digitalWrite(trig_2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_2, LOW);
  
  duration_2= pulseIn(echo_2, HIGH);
  distance_2= duration_2*0.034/2; //speed of sound is known

  //Ultrasonic sensors_2
  if(distance_2 == 7 ){
    //Motors
    analogWrite(rightMotorP, 0); 
    analogWrite(rightMotorN, 130);
    analogWrite(leftMotorP, 0); 
    analogWrite(leftMotorN, 130);
    delay(1000); 
    analogWrite(leftMotorP, 130); 
    analogWrite(leftMotorN, 0);
    delay(1500);
    analogWrite(rightMotorP, 0); 
    analogWrite(rightMotorN, 0);
    analogWrite(rightMotorP, 130); 
    analogWrite(rightMotorN, 0);
    analogWrite(leftMotorP, 130); 
    analogWrite(leftMotorN, 0);
  }
}


void UV3(){
  
  //Ultrasonic sensors_3
  digitalWrite(trig_3, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_3, LOW);
  
  duration_3= pulseIn(echo_2, HIGH);
  distance_3= duration_3*0.034/2; //speed of sound is known
  
  //Ultrasonic sensors_3
  if(distance_3 == 7 ){
    //Motors    
    analogWrite(rightMotorP, 255); 
    analogWrite(rightMotorN, 0);
    analogWrite(leftMotorP, 255); 
    analogWrite(leftMotorN, 0);
    delay(1000);
    analogWrite(rightMotorP, 130);
    analogWrite(rightMotorN, 0);
    delay(1500);
    analogWrite(leftMotorP, 0); 
    analogWrite(leftMotorN, 0);
    analogWrite(rightMotorP, 130); 
    analogWrite(rightMotorN, 0);
    analogWrite(leftMotorP, 130); 
    analogWrite(leftMotorN, 0); 
  }
}

void UV4(){
  
  //Ultrasonic sensors_4
  digitalWrite(trig_4, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_4, LOW);
  
  duration_4= pulseIn(echo_2, HIGH);
  distance_4= duration_4*0.034/2; //speed of sound is known

  //Ultrasonic sensors_4
  if( distance_4 == 7){
    //Motors
    analogWrite(rightMotorP, 0); 
    analogWrite(rightMotorN, 130);
    analogWrite(leftMotorP, 0); 
    analogWrite(leftMotorN, 130);
    delay(1000);
    analogWrite(rightMotorP, 130); 
    analogWrite(rightMotorN, 0);
    delay(1500);
    analogWrite(leftMotorP, 0); 
    analogWrite(leftMotorN, 0); 
    analogWrite(rightMotorP, 130); 
    analogWrite(rightMotorN, 0);
    analogWrite(leftMotorP, 130); 
    analogWrite(leftMotorN, 0);
  }
}

