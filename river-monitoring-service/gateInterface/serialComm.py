import serial

def serial_send(port, baudrate, message):
    try:
        ser = serial.Serial(port, baudrate, timeout=1)

        if not message.endswith('\n'):
            message += '\n'

        ser.write(message.encode())

        ser.close()
        print(f"Message sent: {message.strip()}")
    except Exception as e:
        print(f"Failed to send message: {e}")

def serial_read(port, baudrate):
    try:
        ser = serial.Serial(port, baudrate, timeout=1)

        response = ser.readline().decode('utf-8').strip()

        ser.close()
        print(f"Message read: {response}")
        return response
    except Exception as e:
        print(f"Failed to send message: {e}")