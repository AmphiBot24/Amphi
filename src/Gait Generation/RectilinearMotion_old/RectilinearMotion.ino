/*
Rectilinear motion file for 12 segment snake robot
*/


#include <SoftwareSerial.h>

// Create software serial connection to the Pololu Servo Board
SoftwareSerial pololuSerial(10, 11); // RX, TX pins

// Define servo IDs for the Pololu board (0-5 for the first 6 channels)
int s1 = 1;
int s2 = 2;
int s3 = 4;
int s4 = 5;
int s5 = 6;
int s6 = 7;
int s7 = 8;
int s8 = 9;
int s9 = 11;
// int s8 = 9;

// Define variables
int flex = 65; // Angle to flex a joint
int delayTime = 5; // Delay between limb movements
int startPause = 5000; // Delay to allow robot placement before movement
int pos = 0;  // Loop counter
int smoothnessDelay = 15;  
int wheelState = 0;
int amplitude = 40; 
int lag = 0.59;

int forwardPin =  15;
int wheelTogglePin = 16;
int leftPin = 17;
int rightPin = 18;

int forwardVal = 0;
int wheelToggleVal = 0;
int leftVal = 0;
int rightVal = 0;

  
void setup() 
{ 
// Set movement pins as inputs
 pololuSerial.begin(9600);

 Serial.begin(9600);
  // setServoPosition(s1, 90+amplitude*cos(3*lag));
  // setServoPosition(s2, 90+amplitude*cos(2*lag)); 
  // setServoPosition(s3, 90+amplitude*cos(1*lag));
  // setServoPosition(s4, 90+amplitude*cos(0*lag));
  // setServoPosition(s5, 90+amplitude*cos(1*lag));
  // setServoPosition(s6, 90+amplitude*cos(2*lag));
  // setServoPosition(s7, 90+amplitude*cos(3*lag));

// Delay to give time to position robot  
   delay(startPause);
} 
  
  
void loop() 
{
//  Read movement pin
  
// Forward motion
    delay(delayTime);
    for(pos = 0; pos < flex; pos +=  1)
    {  

   setServoPosition(s9, 90-pos);
   setServoPosition(s8, 90+2*pos);
   setServoPosition(s7, 90-pos);
      delay(smoothnessDelay);
    }  

     delay(delayTime);
    for(pos = 0; pos < flex; pos +=  1)
    {  
      setServoPosition(s9,90-flex+pos);
      setServoPosition(s8,90+2*flex-3*pos);
      setServoPosition(s7,90-flex+3*pos);
      setServoPosition(s6,90-pos);
      delay(smoothnessDelay);
    } 

     delay(delayTime);
    for(pos = 0; pos < flex; pos +=  1)
    {  
      setServoPosition(s8,90-flex+pos);
      setServoPosition(s7,90+2*flex-3*pos);
      setServoPosition(s6,90-flex+3*pos);
      setServoPosition(s5,90-pos);
      delay(smoothnessDelay);
    } 

    delay(delayTime);
    for(pos = 0; pos < flex; pos +=  1)
    {  
      setServoPosition(s7,90-flex+pos);
      setServoPosition(s6,90+2*flex-3*pos);
      setServoPosition(s5,90-flex+3*pos);
      setServoPosition(s4,90-pos);
      delay(smoothnessDelay);
    } 

    delay(delayTime);
    for(pos = 0; pos < flex; pos +=  1)
    {  
      setServoPosition(s6,90-flex+pos);
      setServoPosition(s5,90+2*flex-3*pos);
      setServoPosition(s4,90-flex+3*pos);
      setServoPosition(s3,90-pos);
      delay(smoothnessDelay);
    } 

    delay(delayTime);
    for(pos = 0; pos < flex; pos +=  1)
    {  
      setServoPosition(s5,90-flex+pos);
      setServoPosition(s4,90+2*flex-3*pos);
      setServoPosition(s3,90-flex+3*pos);
      setServoPosition(s2,90-pos);
      delay(smoothnessDelay);
    } 

     delay(delayTime);
    for(pos = 0; pos < flex; pos +=  1)
    {  
      setServoPosition(s4,90-flex+pos);
      setServoPosition(s3,90+2*flex-3*pos);
      setServoPosition(s2,90-flex+3*pos);
      setServoPosition(s1,90-pos);
      delay(smoothnessDelay);
    } 
     delay(delayTime);
    for(pos = 0; pos < flex; pos +=  1)
    {  
      setServoPosition(s3,90-flex+pos);
      setServoPosition(s2,90+2*flex-2*pos);
      setServoPosition(s1,90-pos);
      delay(smoothnessDelay);
    } 

    unsigned int position1 = getServoPosition(1); // Channel 0
  Serial.print("Servo Position 1 : ");
  Serial.println(position1);
 

  unsigned int position = getServoPosition(2); // Channel 0
  Serial.print("Servo Position: ");
  Serial.println(position);
 
 
    // delay(delayTime);
    // for(pos = 0; pos < flex; pos +=  1)
    // {  
    //   setServoPosition(s4,90-flex+pos);
    //   setServoPosition(s3,90+2*flex-2*pos);
}

void setServoPosition(int servo, int angle) {
  int pulseWidth = map(angle, 0, 180, 4000, 8000); // Convert angle to pulse width in microseconds (e.g., 4000-8000 for 0-180 degrees)

  // Create and send the Pololu Maestro command
  pololuSerial.write(0x84); // Command byte: Set Target
  pololuSerial.write(servo); // Channel number
  pololuSerial.write(pulseWidth & 0x7F); // Low bits of target (7 bits)
  pololuSerial.write((pulseWidth >> 7) & 0x7F); // High bits of target (7 bits)
}

unsigned int getServoPosition(unsigned char channel) {
  pololuSerial.write(0x90);           // Command byte: Get Position
  pololuSerial.write(channel);        // Channel number
  unsigned int lowByte = pololuSerial.read();  // Read the lower 7 bits
  unsigned int highByte = pololuSerial.read(); // Read the higher 7 bits
  return (highByte << 8) | lowByte;    // Combine high and low bytes
}