#include <Servo.h>
#include <math.h>
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  

SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
int ledPIN=13; 

 


class Coco{

public:
	Coco (){		
		_servoPIN=6;
		_trigPIN=7;
		_echoPIN=8;
		_distanceMax=15;
                _maxAngle=90+45;
                _minAngle=90;
                
        	   _servoMouth.write(_maxAngle);                
	}

	void init(){
		   _servoMouth.attach(_servoPIN);
		   pinMode(_trigPIN, OUTPUT);
		   pinMode(_echoPIN, INPUT);
		   Serial.begin(9600);
	}
	void activeToBite(){
		   
		   _distance=calcDistance();
   
		   if(_distance<=_distanceMax) bite();
		   else normal();
		   		 
		   Serial.print(_distance);
		   Serial.println("cm");
     
	}

        void setMouthMaxAngle(int maxAngle){
          _maxAngle=maxAngle;
        }
        void setMouthMinAngle(int minAngle){
          _minAngle=minAngle;
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
	   _servoMouth.write(_maxAngle);
	}


	int calcDistance(){
	    long duration;
	    digitalWrite(_trigPIN, LOW);  // Added this line
	    delayMicroseconds(2); // Added this line
	    digitalWrite(_trigPIN, HIGH);
	    delayMicroseconds(10); // Added this line
	    digitalWrite(_trigPIN, LOW);
	    duration = pulseIn(_echoPIN, HIGH);
	    _distance = (duration/2) / 29.1; 
		
	  	return  (int) _distance;
	}


         Servo _servoMouth;  // create servo object to control a servo 
	int _servoPIN;
	int _trigPIN; 
	int _echoPIN;
	int _maxAngle=90+45;
	int _minAngle=90;
	int _distance;
	int _distanceMax;

};

int toInt(char a){
  char b[]={'0','1','2','3','4','5','6','7','8','9'};
  int i;
  for(i=0;i<10;i++)
    if(a==b[i])  return i;
  return -1;
}



 
Coco mCoco;
void setup() 
{ 
   mCoco.init();
   mCoco.setMaxDistance(12);
   pinMode(ledPIN,OUTPUT);
   BT.begin(9600);       // Inicializamos el puerto serie BT que hemos creado
    
} 
 



boolean execute=false,bite=false,finish=false;
int times=0;
void loop() 
{ 
  if(execute && bite) { //ejecutar  
    mCoco.activeToBite();
    digitalWrite(ledPIN,HIGH);    
  }
  else digitalWrite(ledPIN,LOW);    
  
  
  if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    char c=BT.read();
    Serial.write(c);
    
    //input de otra aplicacion
    switch(c){
      case 'e':
          execute=true;
      break;
      case 'b':
          bite=true;
      break;
    
    }

    
    
    
  }
  
  
 /*
  if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
     BT.write(Serial.read());
  }*/
   delay(300);
} 

