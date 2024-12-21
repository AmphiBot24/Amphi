#include <SCServo.h>

#define S_RXD 18
#define S_TXD 19
#define servoID 1

float feedbackThreshold = 0.5;

SMS_STS st;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
  st.pSerial = &Serial1;
  st.WritePosEx(servoID, 2047, 10, 2);
  delay(3000);
  Serial.print("INITIAL"); // Set all servos to initial position

}

void loop(){}
// {
//   int targetAngle= 20;
//   int targetPosition = angleToPosition(targetAngle);
//   st.WritePosEx(servoID, targetPosition, 1500, 50); //To control the servo with ID 1, rotate it to position 1000 at a speed of 1500, with a start-stop acceleration of 50.
//   delay(754);
//   Serial.print("1st");
//   int currentPosition = st.ReadPos(servoID);
//   float currentAngle = positionToAngle(currentPosition);

//   float error = abs(currentAngle - targetAngle);
//     if (error > feedbackThreshold) {
//     Serial.print("Correcting Servo ");
//       Serial.print(servoID);
//       Serial.print(" Error: ");
//       Serial.println(error);

//       st.WritePosEx(servoID, targetPosition, 1500, 50);
//     }

//     // Print debug information
//     Serial.print("Servo ");
//     Serial.print(servoID);
//     Serial.print(" Target: ");
//     Serial.print(targetAngle);
//     Serial.print("° Current: ");
//     Serial.print(currentAngle);
//     Serial.println("°");  

//   targetAngle=-30;
//   targetPosition = angleToPosition(targetAngle);
//   st.WritePosEx(servoID, targetPosition, 1500, 50); // To control the servo with ID 1, rotate it to position 20 at a speed of 1500, with a start-stop acceleration of 50.
//   delay(754);
//   Serial.print("2nd");
//   currentPosition = st.ReadPos(servoID);
//   currentAngle = positionToAngle(currentPosition);

//   error = abs(currentAngle - targetAngle);
//     if (error > feedbackThreshold) {
//     Serial.print("Correcting Servo ");
//     Serial.print(servoID);
//       Serial.print(" Error: ");
//       Serial.println(error);

//       st.WritePosEx(servoID, targetPosition, 1500, 50);
    
//     }
//     // Print debug information
//     Serial.print("Servo ");
//     Serial.print(servoID);
//     Serial.print(" Target: ");
//     Serial.print(targetAngle);
//     Serial.print("° Current: ");
//     Serial.print(currentAngle);
//     Serial.println("°");  //[(P1-P0)/V]*1000+100
// }

// float positionToAngle(int position) {
//   return map(position, 0, 4095, -180, 180); // Adjust mapping range based on servo specs
// }

// int angleToPosition(float angle) {
//   return map(angle, -180, 180, 0, 4095); // Adjust mapping range based on servo specs
// }