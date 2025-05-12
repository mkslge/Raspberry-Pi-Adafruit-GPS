# GPS Data Reader for Adafruit Ultimate GPS HAT on Raspberry Pi 4/5

A lightweight C program that reads real-time GPS data (latitude and longitude) from the Adafruit GPS HAT on Raspberry Pi 4 or 5.
## Requirements

- **Raspberry Pi 5** (other models may work, but this code is optimized for the Raspberry Pi 4/5).
- **Adafruit GPS HAT**
- **Make sure your GPS Hat can see the Sky (Preferrably Outside, or right next to a window)**
## Installation

1. **Connect your Adafruit GPS HAT to the Raspberry Pi**:
   - Make sure that the GPS HAT is securely connected to your Raspberry Pi

2. **Enable serial communication on the Raspberry Pi**:
   - Open a terminal on your Raspberry Pi and run:
     ```bash
     sudo raspi-config
     ```
   - Navigate to **Interface Options** > **Serial** and enable the serial interface.
   - Disable the serial console


## Building and Running the Code

1. **Compiling the code**:  
   Open a terminal and navigate to the directory where you have `gps.c`. Then, run the following command to compile the code:
   ```bash
   make run

