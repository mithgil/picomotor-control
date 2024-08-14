#include <libserial/SerialPort.h>
#include <iostream>

using namespace LibSerial;

int main() {
    
    SerialPort serial_port;

    try {
        // Open the serial port
        serial_port.Open("/dev/ttyUSB0");

        // Configure the port
        serial_port.SetBaudRate(BaudRate::BAUD_9600);

        // Send the command
        std::string command = "1PR -200\r\n";
        serial_port.Write(command);

        // Read the response (optional)
        std::string response;
        serial_port.Read(response);
        std::cout << response << std::endl;

        // Close the port
        serial_port.Close();
        
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}