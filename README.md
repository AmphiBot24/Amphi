# Amphi

## Overview

The Amphibious Snake Bot is a modular, bio-inspired robot with 8 DOF, capable of operating on land and in water for search, inspection, and disaster monitoring. It moves using slithering, rectilinear, and sidewinding motion on land, while undulatory propulsion enables efficient swimming.

Each module has a high-torque bus servo and an independent 7.4V 850mAh battery, ensuring decentralized functionality and balanced power distribution. The ESP32 camera in the head module provides real-time imaging and crack detection, while the ESP32 Servo Driver Expansion Board handles servo coordination via serial communication.

Its waterproof 3D-printed body ensures durability in underwater operations, and optional wheel attachments enhance mobility on flat surfaces. Sensor integration, including a thermal camera, enables real-time video capture and environmental monitoring. 

With modular scalability, adaptive locomotion, and multi-terrain capabilities, the bot is ideal for search and rescue, disaster inspection, and industrial monitoring in harsh and confined environments.

## Directory Structure

The repository is organized into several main directories, each serving a specific purpose:

- **assets/**
  - **cad/**: Contains CAD files related to the project.

- **docs/**
  - **Smart India Hackathon PPT/**: Contains presentation files for the Smart India Hackathon.

- **helper/**
  - **ServoDriverST/**: Contains helper files for the Servo Driver ST.

- **src/**
  - **Crack_Detection/**: Contains files related to crack detection.
  - **Gait Generation/**: Contains files related to gait generation.
    - **1_servo_feedback_test/**: Contains files for testing servo feedback.
    - **Know_the_Servo_ID/**: Contains files for identifying the servo ID.
    - **RectilinearMotion_old/**: Contains files for old rectilinear motion algorithms.
    - **Slithering_Motion_HTTP/**: Contains files for slithering motion controlled via HTTP.
    - **Slithering_Motion_Keypress/**: Contains files for slithering motion controlled via keypress.
    - **Slithering_Motion_old/**: Contains old files for slithering motion.
    - **Slithering_Motion_Satyak/**: Contains files for slithering motion (Satyak's implementation).
    - **slither_with_fb/**: Contains files for slithering motion with feedback.
    - **smooth_slither_wo_feedback/**: Contains files for smooth slithering motion without feedback.

- **.git/**: Contains git-related files and directories.

## Installation

Provide instructions on how to install and set up the project.

## Usage

Provide instructions on how to use the project, including any necessary commands or configurations.

## Contributing

Provide guidelines for contributing to the project, including how to submit issues and pull requests.

## License

Include the project's license information.

## Acknowledgements

Include any acknowledgements or credits for the project.
