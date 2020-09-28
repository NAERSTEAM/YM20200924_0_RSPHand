
//Sep 28 2020. T.I. removed the case "0" for the serial command parser 
//Sep 28 2020. T.I. created this file


#include <Servo.h>

#define ZEROPOSITION 500  //micro seconds, 0 degree 
#define ENDPOSITION 2400  //micro seconds, 180 degree 
#define GRABDEGREE 0
#define RELEASEDEGREE 90

Servo servo_n[3]; 

int incomingByte = 0;

void setup() {

  // put your setup code here, to run once:

    Serial.setTimeout(50);
    Serial.begin(9600);

    servo_n[0].attach(9, ZEROPOSITION, ENDPOSITION);
    servo_n[1].attach(10, ZEROPOSITION, ENDPOSITION);
    servo_n[2].attach(11, ZEROPOSITION, ENDPOSITION);

}

void loop() {
  
  // put your main code here, to run repeatedly:

  int i = 0;

  
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();


    if('1'==incomingByte)
    {
          Serial.println("rock");
    }
    else if('2'==incomingByte)
    {
          Serial.println("scissors");
    }
    else if('3'==incomingByte)
    {
          Serial.println("paper");
          
    }
    else
    {
       
    }
  }

}
