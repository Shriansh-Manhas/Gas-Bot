#include <AFMotor.h>
#include <NewPing.h> //need to install a lib for this
#include <Servo.h> 

Servo myservo;	// create servo object to control a servo
int pos = 0;	// variable to store the servo position

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
int distance = 100;

void setup() 
{
	// attaches the servo on pin 10 to the servo object
	myservo.attach(10);   
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

int checkleft(){
  for(pos = 0; pos <= 90; pos += 1) 
	{
		myservo.write(pos);
		delay(15);
	}
  int dist = readPing();
  delay(2000);
	// sweeps from 90 degrees to 0 degrees
	for(pos = 90; pos>=0; pos-=1)
	{
		myservo.write(pos);
		delay(15);
	}
  return dist;
}

int checkright(){
  for(pos = 0; pos >= -90; pos -= 1) 
	{
		myservo.write(pos);
		delay(15);
	}
	// sweeps from -90 degrees to 0 degrees
	for(pos = -90; pos<=0; pos+=1)
	{
		myservo.write(pos);
		delay(15);
	}
  int dist = readPing();
  delay(2000);
}

void loop() 
{
	// sweeps from 0 degrees to 180 degrees
	//call fxns
}