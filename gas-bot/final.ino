#include <AFMotor.h>
#include <NewPing.h> //need to install a lib for this
#include <Servo.h> 
#include <Deque.h>

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
int actions[4];
Servo myservo;	// create servo object to control a servo
boolean goesForward=false;
int distance = 100;
int speedSet = 0;
int duration = 0;
int state;
Deque<int> movelist = Deque<int>(50);

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 190 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

float pinSensor = A5;
float gasValue;
float prevgasValue;

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  Serial.print("Distance measured is :- ");
  Serial.println(cm);
  return cm;
}

int checkRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int checkLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

  
void forward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
  //  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  //  {
  //   motor1.setSpeed(speedSet);
  //   motor2.setSpeed(speedSet);
  //   motor3.setSpeed(speedSet);
  //   motor4.setSpeed(speedSet);
  //   delay(5);
  //  }
  }
}

void backward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  // for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  // {
  //   motor1.setSpeed(speedSet);
  //   motor2.setSpeed(speedSet);
  //   motor3.setSpeed(speedSet);
  //   motor4.setSpeed(speedSet);
  //   delay(5);
  // }
}  

void right() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);     
  delay(500);
} 
 
void left() {
  motor1.run(BACKWARD);     
  motor2.run(FORWARD);  
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  delay(500);
}  
void oneeighty(){
  right();
  right();
}

void stop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void detect(){
  int dis = readPing();
  int leftdis,rightdis;
  if(dis <= 15)
  {
    stop();
    leftdis = checkLeft();
    rightdis = checkRight();
      if(rightdis<15){
        right();
        state = 1;
      }
      else if(leftdis < 15){
        left();
        state = 1;
      }
  }
}

void setup() {
  // put your setup code here, to run once:
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  motor3.setSpeed(100);
  motor4.setSpeed(100);
  myservo.attach(10);   
  myservo.write(115); 
  pinMode(pinSensor, INPUT);
  Serial.begin(9600);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  movelist.push_back(0);
  movelist.push_back(0);
  state = 1;
}


void loop() {
  forward();
  backward();
  backward();
  forward();
  left();
  forward();
  backward();
}
