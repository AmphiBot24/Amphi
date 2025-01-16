#include <math.h>
#include <SCServo.h>

SMS_STS st;
#define S_RXD 18
#define S_TXD 19

// Define motor constants
#define NUM_MOTORS 4
int motor_ids[NUM_MOTORS] = {1,3,5,7}; // Servo IDs
int speed = 3000;  // Speed of servo movement
int accel = 150;    // Acceleration of servo movement

// Motion parameters
float amplitude = 45.0; // Maximum angle in degrees
float frequency = 0.5;  // Fre  quency of oscillation in Hz
float phase_diff = M_PI / 6.0; // Phase difference between motors

void setup() {
  Serial.begin(115200);
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
  st.pSerial = &Serial1;

  // Initialize servos
  for (int i = 0; i < NUM_MOTORS; i++) {
    st.WritePosEx(motor_ids[i], 2048, speed, accel); // Set all servos to initial position
  }

  delay(2000); // Allow servos to stabilize
}

void loop() {
  static unsigned long last_update_time = 0;
  static float time_elapsed = 0;

  unsigned long current_time = millis();
  float delta_time = (current_time - last_update_time) / 1000.0; // Time in seconds
  time_elapsed += delta_time;
  last_update_time = current_time;
  int j=1;
  // Generate smooth sinusoidal motion for each motor
  for (int i = 0; i < NUM_MOTORS; i++) {
    float angle = amplitude * sin(2 * M_PI * frequency * time_elapsed + (2.5*(i-j)) * phase_diff);
    int position = map(angle, -180, 180, 0, 4095); // Convert angle to servo position
    st.WritePosEx(motor_ids[i], position, speed, accel);
  }

  

  delay(10); // Small delay to prevent overwhelming the communication
}
