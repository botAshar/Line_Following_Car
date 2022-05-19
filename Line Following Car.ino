
#include <Servo.h>

Servo myservo;  // create servo object to control a servo


int pos = 71;    // variable to store the servo position
int motor=1;         //variable to check if the motor is moving forward, 1 means No.
void setup() 
{
  Serial.begin(38400);
  pinMode(2,INPUT);
  pinMode(4,INPUT);
  pinMode(7,OUTPUT); // motor reverse connection
  pinMode(8,OUTPUT); // motor forward connection
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
}

void loop() 
{
  myservo.write(pos);
  int sensor1Value=digitalRead(2); //reading infrared sensors output
  int sensor2Value=digitalRead(4); //reading infrared sensors output
  
  //checking whether the vehicle is on the track i.e. one of the sensors should be having a 1 output. 
  //1 is the output on the black or non reflective track.
  if(sensor1Value<1 || sensor2Value<1)
  {
        //Turning on the motor
      digitalWrite(8,HIGH);
      digitalWrite(7,LOW);
      motor=0;
      
      
    
    //for debugging
    Serial.print(sensor1Value); 
    Serial.print(",");
    Serial.print(sensor2Value);
    Serial.print("/");
    Serial.println(pos);
    //for debugging

    //if both sensor value is 1 then turn left quickly cause vehicle is on the far left.
    if(sensor1Value>0 && sensor2Value>0)
    {
        while (pos>55) 
        {
          pos=pos+5;//fast turning
        }
        delay(300);//keep same position for 0.3 secs
        
    }
   
    //if left sensor value is 1 then turn left
    else if(sensor1Value>0)
      {
          while (pos>55) 
        {
          pos=pos+1;//slow turning
        }
        delay(300);//keep same position for 0.3 secs
      }
    
    //if Right sensor value is 1 then turn right
    else if(sensor2Value>0 )
      {
        while (pos<87) 
        {
          pos=pos+1; //slow turning
        }
        delay(300);//keep same position for 0.3 secs
      }
  }
  else
    {
      
      while (pos<87) 
        {
          pos=pos+5; //fast turning
        }
    delay(300);//keep same position for 0.3 secs
    
    //if the car is still not on the track it's probably on the finish line or has been lifted. so will stop.
    if(motor=0 && sensor1Value>=1 && sensor2Value>=1 )
      {
          digitalWrite(8,LOW);
          digitalWrite(7,HIGH);// decelerates the car.
          motor=motor+1;
          delay(3000); //decelerates for 3 secs
      }
    
    digitalWrite(7,LOW);
  
  }
}

