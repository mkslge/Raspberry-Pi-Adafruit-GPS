# GPS Data Reader for Adafruit GPS HAT on Raspberry Pi 5

Allows you to get GPS data from an Adafruit GPS HAT connected to a Raspberry Pi 5. The program continuously reads GPS data from the GPS module and prints the longitude and latitude :)

## Requirements

- **Raspberry Pi 5** (other models may work, but this code is optimized for the Raspberry Pi 5).
- **Adafruit GPS HAT** connected to the Raspberry Pi's GPIO pins.
- **Serial interface enabled** on the Raspberry Pi (make sure that the UART is enabled and configured).
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


## Building and Running the Code

1. **Compiling the code**:  
   Open a terminal and navigate to the directory where you have `gps.c`. Then, run the following command to compile the code:
   ```bash
   gcc gps.c -o gps
   sudo ./gps

