import time
import requests
import keyboard  # Install via `pip install keyboard`

# ESP32 Configuration
esp32_ip = "192.168.1.70"
esp32_port = 80
url = f"http://{esp32_ip}:{esp32_port}/command"

# Command and speed variables
commands = {"w": "forward", "a": "left", "s": "backward", "d": "right"}
speed_multiplier = 1
max_speed_multiplier = 5

# Modes
modes = {1: "sinusoidal"}
current_mode = None  # Start with no mode selected

# Function to send commands to ESP32
def send_command(command, speed, mode):
    data = {"command": command, "speed": speed, "mode": mode}
    try:
        response = requests.post(url, json=data)
        print(f"Sent: {data}, Response: {response.text}")
    except Exception as e:
        print(f"Error sending command: {e}")

print("You can change the mode dynamically at any time:")

# Main loop
while True:
        # Dynamically check for mode selection
    for key, mode in modes.items():
        if keyboard.is_pressed(str(key)):  # Listen for numeric keys (1, 2, 3, etc.)
            current_mode = mode
            print(f"Mode changed to: {current_mode}")
            time.sleep(0.2)
            
    if current_mode:
        for key, command in commands.items():
            if keyboard.is_pressed(str(key)):
                speed_multiplier = min(speed_multiplier + 1, max_speed_multiplier)
                print(speed_multiplier)
                if current_mode:  # Ensure a mode is selected
                    print('hi')
                    #send_command(command, speed_multiplier, current_mode)
                else:
                    print("Please select a mode before controlling the robot.")
                time.sleep(0.2)  # Small delay to avoid repeated fast triggering

    # Exit condition
    if keyboard.is_pressed("q"):
        print("Exiting...")
        break

