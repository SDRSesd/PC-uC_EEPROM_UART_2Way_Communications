import serial
import time

# Open the serial connection (adjust COM port for your system)
ser = serial.Serial('COM4', 2400, timeout=1)  # Adjust COM port if necessary
time.sleep(2)  # Give Arduino time to reset

data_to_send = b"Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting that the next banking crisis would be triggered by MSME lending, saying postmortem is easier than taking action when it was required. Rajan, who had as the chief economist at IMF warned of impending financial crisis of 2008, in a note to a parliamentary committee warned against ambitious credit targets and loan waivers, saying that they could be the sources of next banking crisis. Government should focus on sources of the next crisis, not just the last one. In particular, government should refrain from setting ambitious credit targets or waiving loans. Credit targets are sometimes achieved by abandoning appropriate due diligence, creating the environment for future NPAs, Rajan said in the note. Both MUDRA loans as well as the Kisan Credit Card, while popular, have to be examined more closely for potential credit risk. Rajan, who was RBI governor for three years till September 2016, is currently."  # Data to send
bytes_sent = 0
start_time = time.time()

# Sending data byte by byte with delay and checking for received data
for byte in data_to_send:
    ser.write(byte.to_bytes(1, 'big'))  # Send 1 byte
    bytes_sent += 1

    # Delay to prevent overwhelming the serial port
    time.sleep(0.05)

    # Receive and print the echoed byte, if any
    if ser.in_waiting > 0:
        received_byte = ser.read(1)
        print(f"Received: {received_byte.decode(errors='ignore')}")  # Decode and print as string

    # Calculate speed every second
    if time.time() - start_time >= 1:
        bps = bytes_sent * 8  # Convert bytes to bits
        print(f"Live Transmission Speed: {bps} bps")
        start_time = time.time()  # Reset the timer
        bytes_sent = 0  # Reset the byte counter for the next second

ser.close()  # Close the serial connection when done
