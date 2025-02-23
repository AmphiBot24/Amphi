import numpy as np
import matplotlib.pyplot as plt

# Parameters
frequency = 5  # Oscillation frequency in Hz
amplitude = 40   # Amplitude of the serpentine motion
counter = np.arange(0, 40, 1)  # Counter values from 0 to 360
num_servos = 2    # Number of servos

# Phase lag between segments for each servo
lag = 0.59  # Phase lag (radians)

# Create a figure for plotting
plt.figure(figsize=(12, 8))

# Loop over all servos (motors) and apply a phase shift
for i in range(1, num_servos + 1):
    # Phase shift for each motor based on its index
    phase_shift = (i - 1) * lag  # Increasing phase shift for each motor
    
    # Generate the continuous sine wave for each servo (position)
    position = 90 + amplitude * np.sin((2 * np.pi * frequency * counter / 360) + phase_shift)
    
    # Plot the discrete points for each motor (position)
    plt.scatter(counter, position, label=f"Motor {i} (Phase shift {phase_shift:.2f})", s=20)

# Customize plot
plt.title("Servo Position Variation with Phase Lag (Continuous Sine Wave)", fontsize=16)
plt.xlabel("Counter (degrees)", fontsize=14)
plt.ylabel("Position", fontsize=14)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(fontsize=12)
plt.show()
