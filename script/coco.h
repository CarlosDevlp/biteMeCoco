#include <Servo.h>

class Coco{

public:
	Coco (){		
		_servoPIN=11;
		_trigPIN=13;
		_echoPIN=12;
		_distanceMax=15;
	}

	void init(){
		   _servoMouth.attach(_servoPIN);
		   pinMode(_trigPIN, OUTPUT);
		   pinMode(_echoPIN, INPUT);
		   Serial.begin(9600);
	}
	void activeToBite(){
		   
		   _distance=getDistance();
   
		   if(_distance<=_distanceMax) bite();
		   else normal();
		   
		  

		   Serial.print(_distance);
		   Serial.println("cm");
   
	}

	void setMaxDistance(int distanceMax){
		_distanceMax=distanceMax;
	}

	int getDistance(){
		return _distance;
	}

private:
	
	void bite(){
	  int a;
	  
	  //bajar la mandibula
	  for(a=_maxAngle;a>=_minAngle;a--){
	    _servoMouth.write(a);
	    delay(0);
	  }
	  //subir la mandibula  
	  for(a=_minAngle;a<_maxAngle;a++){
	    _servoMouth.write(a);
	    delay(20);
	  }
	  
	}

	void normal(){
	   _servoMouth.write(maxAngle);
	}


	int calcDistance(){
	    long duration;
	    digitalWrite(_trigPIN, LOW);  // Added this line
	    delayMicroseconds(2); // Added this line
	    digitalWrite(_trigPIN, HIGH);
	    delayMicroseconds(10); // Added this line
	    digitalWrite(_trigPIN, LOW);
	    duration = pulseIn(echoPin, HIGH);
	    _distance = (duration/2) / 29.1; 
		
	  	return  (int) _distance;
	}


	int Servo _servoMouth;  // create servo object to control a servo 
	int _servoPIN;
	int _trigPIN; 
	int _echoPIN;
	int _maxAngle=90+45;
	int _minAngle=90;
	int _distance;
	int _distanceMax;

};
