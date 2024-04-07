import sys
import serial

def parse_file_contents(file_path):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
            parsed_numbers = []
            for line in lines[:20]:  # Read a maximum of 20 lines
                numbers = line.strip().split(',')
                parsed_numbers.append(','.join(numbers) + ',')
            return '$&' + ''.join(parsed_numbers)[:-1] + '%'
    except FileNotFoundError:
        print(f"File '{file_path}' not found.")
        return None

if len(sys.argv) < 3:
    print("Usage: python script.py <file_path> <serial_port>")
    exit(1)

file_path = sys.argv[1]
serial_port = sys.argv[2]

print("Hello, world!")
print("Arguments passed:", sys.argv)

formatted_numbers = parse_file_contents(file_path)
if formatted_numbers is not None:
    print("Formatted numbers:", formatted_numbers)

    # Initialize serial connection
    try:
        ser = serial.Serial(serial_port, baudrate=115200, timeout=1)
    except serial.SerialException as e:
        print("Error opening serial port:", e)
        exit(1)

    # Send formatted numbers through USART
    try:
        ser.write(formatted_numbers.encode())
        print("Formatted numbers sent through USART.")
    except serial.SerialException as e:
        print("Error sending data through USART:", e)
        ser.close()
        exit(1)

    ser.close()
else:
    exit(1)
exit(0)
