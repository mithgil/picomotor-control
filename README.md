# picomotor-control

Using Terminal Code or Scripts to Drive Newport Picomotor in Linux

2024/8/14

There are a few alternative python projects available about controlling Picomotor. None of these projects offers a comprehensive guide for a Linux user from scratch. The complete manual for Picomotor and relevant documents are available on the official [website](https://www.newport.com/f/open-loop-picomotor-motion-controller). Here is a comprehesive guide to Picomotor controller through terminal or scripts from basic settings to coding step by step. A python script and a CMake c++ project are provided.

## Step 1: Install minicom

If you don’t have minicom installed, you can install it via your package manager:

```bash
sudo apt-get install minicom
```

## Step 2: Identify the USB device

Plug in your Newport Picomotor Controller via USB and find the associated device file:

```bash
dmesg | grep tty
```

This command should show you something like `/dev/ttyUSB0` or `/dev/ttyACM0`.

## Step 3: Configure minicom

Launch minicom with the following command to configure the serial port:

```bash
sudo minicom -s
```

- Choose Serial port setup.
- Set the serial device to /dev/ttyUSB0 or whatever your device was identified as.
- Configure the baud rate to match the controller’s settings (typically 9600, 8N1 for RS485).
- Press Enter to confirm.
- Save configuration:

After setting up, you can save the configuration for future use.
Exit back to the main menu and select Save setup as dfl (default).
Exit setup and start communication:

After saving, choose Exit Linux user from the configuration menu to start using minicom with the controller.

## Step 4. Install usbutils and Load USB device

If you don’t see the device, make sure you have usbutils installed:

```bash
sudo apt-get install usbutils
```

This ensures you have the necessary utilities to list and diagnose USB devices.

show usb device
```bash
lsusb
```
and it should print something like:
`Bus 001 Device 010: ID 104d:4000 Newport Corporation Picomotor Controller`

where the ID is a crucial information.

Try Loading USB Serial Drivers with previous info:
```bash
sudo modprobe usbserial vendor=0x104d product=0x4000
```
Then check if a `/dev/ttyUSB*` device appears.
**Note** this step is very **important**! Otherwise, you will give up programming in Linux.


## Step 5. Check Permissions

```bash
ls /dev/ttyUSB*
```

You should see something like `/dev/ttyUSB0`. 

If you see the device but can’t access it, you may need to adjust permissions:

```bash
sudo chmod 666 /dev/ttyUSB0
```

Replace /dev/ttyUSB0 with your device path.

## Step 6. Open minicom with the appropriate serial device

Replace /dev/ttyUSB0 with the correct serial device name.

Configure Serial Settings:

Press Ctrl + A, then Z to open the minicom help menu.
Press O to configure minicom.
Navigate to "Serial port setup" and set the following parameters:

- A. Serial Device: Ensure it's set to /dev/ttyUSB0 or your specific port.
- E. Bps/Par/Bits: Match the baud rate, parity, and stop bits required by the device (common settings might be 9600 8N1).
- F. Hardware Flow Control: Set to No.
- G. Software Flow Control: Set to No.

Save and Connect:

Exit the configuration menu and minicom will attempt to connect to the device.

### Accessing the terminal of the Picomotor device

1. Sending Commands
    In the terminal, simply type the command followed by pressing Enter. For example, to send a command to move a motor, you might enter:
   
   ```plaintext
   1PR 5000
   ```
   
    This command would tell motor 1 to move to the position 5000 (assuming this is the correct syntax).

2. Command Format
    Newport Picomotor Controllers typically have a specific command syntax. Commands usually consist of a motor number, an action (like "PR" for "position relative"), and parameters (like the position value). Here's a general format:
   
   ```plaintext
   <MOTOR_NUMBER><COMMAND><PARAMETERS>
   ```
   
    Some examples might include:
   
   ```
   1PR 5000: Move motor 1 by 5000 steps relative to its current position.
   1PA 10000: Move motor 1 to an absolute position of 10000.
   1ST: Stop motor 1 immediately.
   VE?: Query the current velocity.
   ```

3. Checking Responses
    After sending a command, the device should respond with either an acknowledgment or the requested data. For example, if you send a query command like 1TP? (which queries the position), the controller should return the current position of motor 1.

4. Common Commands
    Here are some common commands you might use:
   
   ```
   1PR <steps>: Move motor 1 by a relative number of steps.
   1PA <position>: Move motor 1 to an absolute position.
   1TP?: Query the current position of motor 1.
   1VE <velocity>: Set the velocity for motor 1.
   1ST: Stop motor 1.
   VE?: Query the current velocity.
   ```

5. Using minicom
    If you are using minicom, just type the commands directly into the terminal window. Ensure that minicom is correctly configured to send carriage returns (CR) or line feeds (LF) as required by your device.

## Alternative Method: Using a Python Script
Before running the python script, you need to do

```bash
chmod 666 /dev/ttyUSB0
```

or 

```bash
$ sudo adduser $USER dialout
```
**One must log out and back in before these group changes come into effect.**

Since the current user is not part of the dialout group. This will add the current user to the dialout group.

Please refer to the [website](https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/) for more details

where `/dev/ttyUSB0` is the USB device you found in the terminal.

Example Python Script
with `pyserial` library:

```python
import serial

# Open serial connection (replace '/dev/ttyUSB0' with your device's port, baudrate = 9600 since RS485)
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1) 

# Send command to move motor 1 by 5000 steps
ser.write(b'1PR 5000\r\n')
    
# Close the csonnection
ser.close() 
```

This script sends the `1PR 5000` command and prints any response Linux user from the controller.

Another similiar cmake project is also provided if you prefer c++. 
