# GPS Data Reader for Adafruit GPS HAT on Raspberry Pi 5

This project allows you to get GPS data from an Adafruit GPS HAT connected to a Raspberry Pi 5. The code reads and converts GPS coordinates from DMM format to decimal degrees and prints them to the terminal. The program continuously reads GPS data from the GPS module via the serial port.

## Requirements

- **Raspberry Pi 5** (other models may work, but this code is optimized for the Raspberry Pi 5).
- **Adafruit GPS HAT** connected to the Raspberry Pi's GPIO pins.
- **Serial interface enabled** on the Raspberry Pi (make sure that the UART is enabled and configured).
- **GCC compiler** to compile the C code.

## Installation

1. **Connect your Adafruit GPS HAT to the Raspberry Pi**:
   - Make sure that the GPS HAT is securely connected to your Raspberry Pi via the GPIO pins.

2. **Enable serial communication on the Raspberry Pi**:
   - Open a terminal on your Raspberry Pi and run:
     ```bash
     sudo raspi-config
     ```
   - Navigate to **Interface Options** > **Serial** and enable the serial interface.
   - Disable the serial console if prompted.
   
3. **Install the necessary dependencies**:
   If you don't have GCC installed on your Raspberry Pi, install it by running:
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential

## Building and Running the Code

1. **Compile the code**:  
   Open a terminal and navigate to the directory where you have `gps.c`. Then, run the following command to compile the code:
   ```bash
   gcc gps.c -o gps

   ## Run the program
  ```bash
  sudo ./gps
