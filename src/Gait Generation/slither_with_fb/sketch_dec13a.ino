#include <SCServo.h>
#include <math.h>

// Servo setup
SMS_STS st;
#define S_RXD 18
#define S_TXD 19
#define NUM_SERVOS 8 // Number of servos

// Motion parameters
float amplitude = 30.0; // Amplitude of sine wave (degrees)
float wavelength = 2.0; // Wavelength of sine wave (servos per cycle)
float frequency = 0.1;  // Speed of wave (cycles per second)
int speed = 1000;       // Speed for servo movement
int accel = 50;         // Acceleration for smooth motion
float timeStep = 0.05;  // Time increment for wave (seconds)
float feedbackThreshold = 5.0; // Allowed deviation (degrees) for error correction

// Servo IDs
int servoIDs[NUM_SERVOS] = {1, 2, 3, 4,5,6,7,8};

// Time tracker
float t = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
  st.pSerial = &Serial1;
  delay(1000);

  Serial.println("Snake Bot Slithering Motion");
}

void loop() {
  // Generate slithering motion
  for (int i = 0; i < NUM_SERVOS; i++) {
    float targetAngle = amplitude * sin(2 * M_PI * (t - (i / wavelength)));
    int targetPosition = angleToPosition(targetAngle);

    // Write target position
    st.WritePosEx(servoIDs[i], targetPosition, speed, accel);

    // Read feedback and correct position if necessary
    int currentPosition = st.ReadPos(servoIDs[i]);
    float currentAngle = positionToAngle(currentPosition);

    float error = abs(currentAngle - targetAngle);
    if (error > feedbackThreshold) {
      Serial.print("Correcting Servo ");
      Serial.print(servoIDs[i]);
      Serial.print(" Error: ");
      Serial.println(error);

      st.WritePosEx(servoIDs[i], targetPosition, speed, accel);
    }

    // Print debug information
    Serial.print("Servo ");
    Serial.print(servoIDs[i]);
    Serial.print(" Target: ");
    Serial.print(targetAngle);
    Serial.print("° Current: ");
    Serial.print(currentAngle);
    Serial.println("°");
  }

  // Increment time for the next wave step
  t += timeStep;
  //delay(timeStep * 1000); // Convert seconds to milliseconds
}

// Convert angle (degrees) to servo position (internal units)
int angleToPosition(float angle) {
  return map(angle, -90, 90, 0, 4095); // Adjust mapping range based on servo specs
}

// Convert servo position (internal units) to angle (degrees)
float positionToAngle(int position) {
  return map(position, 0, 4095, -90, 90); // Adjust mapping range based on servo specs
}
