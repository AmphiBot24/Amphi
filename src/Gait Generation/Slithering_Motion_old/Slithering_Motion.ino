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

int counter = 0; // Loop counter variable
float lag =0.59; // Phase lag between segments
int frequency = 1; // Oscillation frequency of segments.
int amplitude = 40; // Amplitude of the serpentine motion of the snake
int rightOffset = 5; // Right turn offset
int leftOffset = -5; // Left turn offset
int offset = 0; // Variable to correct servos that are not exactly centered
int delayTime = 0; // Delay between limb movements
int startPause = 5000;  // Delay time to position robot

void setup() 
{ 
  // Start software serial communication
  pololuSerial.begin(9600);

Serial.begin(9600);

   setServoPosition(s1,90+offset+amplitude*sin(4*lag));
   setServoPosition(s2,90+offset+amplitude*sin(3*lag)); 
   setServoPosition(s3,90+offset+amplitude*sin(2*lag));
   setServoPosition(s4,90+amplitude*sin(1*lag));
   setServoPosition(s5,90+amplitude*sin(0*lag));
   setServoPosition(s6,90+amplitude*sin(-1*lag));
   setServoPosition(s7,90+amplitude*sin(-2*lag));
   setServoPosition(s8,90+amplitude*sin(-3*lag));
   setServoPosition(s9,90+amplitude*sin(-4*lag));
   
  delay(startPause);  // Pause to position robot
} 
  
void loop() 
{
  // Forward motion
  for(counter = 0; counter < 360; counter += 3) {
    delay(delayTime);
    setServoPosition(s1, 90 +offset+ amplitude * sin((frequency * counter * 3.14159 / 180 + 4 * lag)));
    setServoPosition(s2, 90 +offset+ amplitude * sin((frequency * counter * 3.14159 / 180 + 3 * lag)));
    setServoPosition(s3, 90 +offset+ amplitude * sin((frequency * counter * 3.14159 / 180 + 2 * lag)));
    setServoPosition(s4, 90 + amplitude * sin((frequency * counter * 3.14159 / 180 + 1 * lag)));
    setServoPosition(s5, 90 + amplitude * sin((frequency * counter * 3.14159 / 180 )));
    setServoPosition(s6, 90 + amplitude * sin((frequency * counter * 3.14159 / 180 - 1 * lag)));
    setServoPosition(s7, 90 + amplitude * sin((frequency * counter * 3.14159 / 180 - 2 * lag)));
    setServoPosition(s8, 90 + amplitude * sin((frequency * counter * 3.14159 / 180 - 3 * lag)));
    setServoPosition(s9, 90 + amplitude * sin((frequency * counter * 3.14159 / 180 - 4 * lag)));

    // Serial printing the positions of the servos
    // Serial.print("1st servo: ");
    // Serial.println(90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    // Serial.print("2nd servo: ");
    // Serial.println(90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    // Serial.print("3rd servo: ");
    // Serial.println(90 + amplitude * cos(frequency * counter * 3.14159 / 180));
    // Serial.print("4th servo: ");
    // Serial.println(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    // Serial.print("5th servo: ");
    // Serial.println(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
  } // Closing brace for the for loop
}

// Function to set servo position using Pololu protocol
void setServoPosition(int servo, int angle) {
  int pulseWidth = map(angle, 0, 180, 4000, 8000); // Convert angle to pulse width in microseconds (e.g., 4000-8000 for 0-180 degrees)

  // Create and send the Pololu Maestro command
  pololuSerial.write(0x84); // Command byte: Set Target
  pololuSerial.write(servo); // Channel number
  pololuSerial.write(pulseWidth & 0x7F); // Low bits of target (7 bits)
  pololuSerial.write((pulseWidth >> 7) & 0x7F); // High bits of target (7 bits)
}
