#include <math.h>
#include <SCServo.h>

SMS_STS st;
#define S_RXD 18
#define S_TXD 19

// Define motor constants
#define NUM_MOTORS 7
int motor_ids[NUM_MOTORS] = {0, 1, 2, 3, 4, 5, 6}; // Servo IDs 
// int motor_ids[NUM_MOTORS] = {6, 5, 4, 3, 2, 1, 0}; // Servo IDs 
int speed = 3500;  // Speed of servo movement
int accel = 150;   // Acceleration of servo movement

// Motion parameters
float amplitude_up_down = 30.0; // Reduced amplitude for up-down DOF (degrees)
float amplitude_left_right = 45.0; // Higher amplitude for left-right DOF (degrees)
float frequency = 1;  // Frequency of oscillation in Hz
float phase_diff = M_PI / 6.0; // Phase difference between motors
float turn_bias = M_PI / 8.0;  // Phase bias for turning left

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

  // Generate motion for each motor
  for (int i = 0; i < NUM_MOTORS; i++) {
    float angle;

    if (i % 2 == 0) {
      // Up-Down DOF motors (even-indexed)
      angle = amplitude_up_down * sin(2 * M_PI * frequency * time_elapsed + i * phase_diff);
    } else {
      // Left-Right DOF motors (odd-indexed)
      angle = -amplitude_left_right * sin(2 * M_PI * frequency * time_elapsed + i * phase_diff + turn_bias); // Changed the sign to change the direction
    }

    int position = map(angle, -180, 180, 0, 4095); // Convert angle to servo position
    st.WritePosEx(motor_ids[i], position, speed, accel);
  }

  delay(10); // Small delay to prevent overwhelming the communication
}
