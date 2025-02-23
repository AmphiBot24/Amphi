import math
import time
import requests

# Define motor constants
NUM_MOTORS = 7
motor_ids = [0, 1, 2, 3, 4, 5, 6]  # Servo IDs
speed = 3500  # Speed of servo movement
accel = 150   # Acceleration of servo movement

# Motion parameters
amplitude_up_down = 30.0  # Reduced amplitude for up-down DOF (degrees)
amplitude_left_right = 45.0  # Higher amplitude for left-right DOF (degrees)
frequency = 1.0  # Frequency of oscillation in Hz
phase_diff = math.pi / 6.0  # Phase difference between motors
turn_bias = math.pi / 8.0  # Phase bias for turning left

# ESP32 Configuration
esp32_ip = "192.168.138.186"
esp32_port = 80  # Default HTTP port
url = f"http://{esp32_ip}:{esp32_port}/"  # Endpoint for the ESP32

# Initialize time
start_time = time.time()

while True:
    try:
        # Calculate elapsed time
        current_time = time.time()
        time_elapsed = current_time - start_time

        # Create a list to hold data for all motors
        servo_data = []

        for i in range(NUM_MOTORS):
            # Determine the motion pattern based on motor index
            if i % 2 == 0:  # Up-Down DOF (even-indexed motors)
                angle = amplitude_up_down * math.sin(2 * math.pi * frequency * time_elapsed + i * phase_diff)
            else:  # Left-Right DOF (odd-indexed motors)
                angle = amplitude_left_right * math.sin(2 * math.pi * frequency * time_elapsed + i * phase_diff + turn_bias)

            # Convert angle to servo position (range: 0 to 4095)
            position = int((angle + 180) * (4095 / 360))  # Map angle (-180 to 180) to (0 to 4095)

            # Append motor data as a dictionary
            servo_data.append({
                "motor_id": motor_ids[i],
                "position": position,
                "speed": speed,
                "accel": accel
            })

        # Send data to the ESP32 via HTTP POST
        response = requests.post(url, json=servo_data)
        print(f"Response from ESP32: {response.text}")

        # Increase the data transmission frequency by reducing sleep time
        time.sleep(0.01)  # Shorter delay (5ms) for higher frequency

    except KeyboardInterrupt:
        print("Stopping the program.")
        break
    except Exception as e:
        print(f"Error occurred: {e}")
        break
