import serial

# Open serial connection (replace '/dev/ttyUSB0' with your device's port)
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)

# Send command to move motor 1 by 5000 steps
ser.write(b'1PR -1000\r\n')

# Read the response (if any)
response = ser.read_until()
print(response.decode())

# Close the connection
ser.close()

