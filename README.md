# EEPROM UART Communication Between PC and Arduino (ATmega328P)

# Project Overview
This project demonstrates two-way communication between a PC and an Arduino UNO via UART, storing received data in the Arduino’s EEPROM. The PC transmits data in chunks of 1024 bytes using Python, while the Arduino receives this data, stores it in its EEPROM, and prints the data along with real-time transmission speed (in bps) on the serial monitor.

# Table of Contents

  Project Overview
  Components Required
  Hardware Setup
  Software Setup
  Future Enhancements


# Components Required
Arduino UNO (ATmega328P)
USB cable (for power and communication)
PC with Python 3.x
Python pyserial library: Used for serial communication


# Hardware Setup
Connect the Arduino UNO to the PC using a "CP2102 USB to UART Bridge converter". The USB connection will handle both power and UART communication.
The UART pins (TX/RX) on the Arduino are handled internally by the USB-to-serial interface, so no external wiring is necessary.

# Software Setup
CP2102 USB to UART brider driver installation - https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
Arduino IDE
Python 3.x
Download Python from the official Python website.

# Python Libraries
Install the pyserial library by running the following command in your terminal:

pip install pyserial

# Future Enhancements
Error Checking: Implement CRC or checksum to verify data integrity.
Higher Baud Rates: Optimize for higher transmission speeds.
Memory Management: Implement paging techniques to handle larger data storage.
GUI: Develop a graphical interface for easier data transmission.


# Note:
  This project is still under progress. Major part is completed & now I'm working on formatting the output to display in User readable format.





