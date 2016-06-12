#include <Servo.h>
#include <math.h>

#define trigPin 13
#define echoPin 12
Servo servoMouth;  // create servo object to control a servo 
 
void setup() 
{ 
   servoMouth.attach(11);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   Serial.begin(9600);
} 
 


void bite();
void normal();


int getDistance(){
    long duration, distance;
    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1; 

  return  (int) distance;
}

int maxAngle=90+45;
int minAngle=90;
int distance,distanceMax=15;
void loop() 
{ 

   distance=getDistance();
   
   if(distance<=distanceMax) bite();
   else normal();
   
  

   Serial.print(distance);
   Serial.println("cm");
   
   
   delay(500);
} 

void bite(){
  int a;
  
  //bajar la mandibula
  for(a=maxAngle;a>=minAngle;a--){
    servoMouth.write(a);
    delay(0);
  }
  //subir la mandibula  
  for(a=minAngle;a<maxAngle;a++){
    servoMouth.write(a);
    delay(20);
  }
  
}

void normal(){
   servoMouth.write(maxAngle);
}
