//Project_RSPImageRobot_20200801_0
//================
//Sep 14 2020 T.I. Added the slow mode for servo motion
//Aug 1 2020 T.I. created this file


#include <Servo.h>

#define ZEROPOSITION 540  //micro seconds, 0 degree 
#define ENDPOSITION 2500  //micro seconds, 180 degree 


#define NUMBER_OF_FINGER 5
#define NUMBER_OF_GESTURE 3
#define maximum_steps 480
#define STEPSPERDEGREE 1

enum GESTUREENUM {
    ROCK_GES,
    SCISSORS_GES,
    PAPER_GES
};


Servo servo_n[NUMBER_OF_FINGER]; 
int servo_nDIR[NUMBER_OF_FINGER]={1,1,0,0,1};  
//servo0 0~120
//servo1 (180-0)~(180-120)


float fingerDegree[NUMBER_OF_FINGER]={0,0,0,0,0}; //0:index ,4:thumb


int incomingByte = 0;
static int lastPos[NUMBER_OF_FINGER];

void setup() {

  // put your setup code here, to run once:

    Serial.setTimeout(50);
    Serial.begin(9600);



    servo_n[0].attach(9, ZEROPOSITION, ENDPOSITION);
    servo_n[1].attach(10, ZEROPOSITION, ENDPOSITION);
    servo_n[2].attach(11, ZEROPOSITION, ENDPOSITION);
    servo_n[3].attach(12, ZEROPOSITION, ENDPOSITION);
    servo_n[4].attach(13, ZEROPOSITION, ENDPOSITION);

    lastPos[0]=0;
    lastPos[1]=0;
    lastPos[2]=0;
    lastPos[3]=0;
    lastPos[4]=0;

}

void loop() {
  
  // put your main code here, to run repeatedly:

  int i = 0;
  int servoGesture;



 

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();



    if(0==incomingByte)
    {
    }
    else if('1'==incomingByte)
    {

        setMotorGesture(ROCK_GES);   
        //handServosMotion();
        handServosMotionSlow();
    }
    else if('2'==incomingByte)
    {

        setMotorGesture(SCISSORS_GES);   
        //handServosMotion();
        handServosMotionSlow();
    }
    else if('3'==incomingByte)
    {
        setMotorGesture(PAPER_GES);   
        //handServosMotion();
        handServosMotionSlow();
      
    }
    else
    {
       
    }
  }



  
}


void handServosMotion()
{
  int i=0;

  
  
  for(i=0;i<NUMBER_OF_FINGER;i++)
  {
   
      if(1==servo_nDIR[i])
      {
         servo_n[i].write(180-(int)fingerDegree[i]);    
      }
      else
      {
         servo_n[i].write((int)fingerDegree[i]);   
    
      }    

  }
}


void handServosMotionSlow()
{
  int i=0;
  int j=0;
  int posc[NUMBER_OF_FINGER];
  

 
  //120*4
  for(i=0;i<maximum_steps;i++)//position commands
  {
     

      for(j=0;j<NUMBER_OF_FINGER;j++)
     {
          posc[j]=lastPos[j];
          if(fingerDegree[j]>lastPos[j])
          {
              if(0==(i%STEPSPERDEGREE))
              {
                  posc[j]=posc[j]+1;
              }
          }
          else if(fingerDegree[j]<lastPos[j])
          {
              if(0==(i%STEPSPERDEGREE))
              {
                  posc[j]=posc[j]-1;
              }
            
          }
          
          if(1==servo_nDIR[j])
          {
             servo_n[j].write(180-posc[j]);    
             lastPos[j]=posc[j];
          }
          else
          {
             servo_n[j].write(posc[j]);
             lastPos[j]=posc[j];
          }    
          

      }
      delay(6);
  }//position commands

  Serial.println(lastPos[0]);
 
  
}


void setMotorGesture(int gesture_number)
{
   
  switch(gesture_number)
  {
    case ROCK_GES:
    {
      fingerDegree[0]=120;
      fingerDegree[1]=120;
      fingerDegree[2]=120;
      fingerDegree[3]=120;
      fingerDegree[4]=120;
          
    }break;
    case SCISSORS_GES:
    {
      fingerDegree[0]=0;
      fingerDegree[1]=0;
      fingerDegree[2]=120;
      fingerDegree[3]=120;
      fingerDegree[4]=120;
    }break;
    case PAPER_GES:
    {
      fingerDegree[0]=0;
      fingerDegree[1]=0;
      fingerDegree[2]=0;
      fingerDegree[3]=0;
      fingerDegree[4]=0;      
    }break;
    default:
    {
      fingerDegree[0]=fingerDegree[0];
      fingerDegree[1]=fingerDegree[1];
      fingerDegree[2]=fingerDegree[2];
      fingerDegree[3]=fingerDegree[3];
      fingerDegree[4]=fingerDegree[4];   
    }
    break;
  }
}
