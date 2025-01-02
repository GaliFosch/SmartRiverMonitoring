from threading import Lock
import time
import serial
from django.conf import settings

class SerialCommunication:
    def __init__(self, port, baudrate = 9600, timeout = 1):
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout
        self.serial = None
        self.lock = Lock()

    def open(self):
        print(self.serial)
        if self.serial is None:
            try:
                self.serial = serial.Serial(
                    port = self.port, 
                    baudrate = self.baudrate, 
                    timeout = self.timeout
                    )
                
                time.sleep(2)
                print(f"Open Connection on port {self.port} with baudrate {self.baudrate}.")
            except Exception as e:
                print(f"Error in serial connection: {e}")
        else:
            try:
                self.serial.open()
                print("Serial connection reopened")
            except Exception as e:
                print("Error failed to reopen connection:")
    
    def close(self):
        if self.isOpen():
            self.serial.close()
            print("Serial Connection closed")

    def isOpen(self):
        return self.serial != None and self.serial.is_open

    def send(self, message):
        try:
            if self.isOpen():
                if not message.endswith('\n'):
                    message += '\n'

                self.serial.write(message.encode())

                print(f"Message sent: {message.strip()}")
            else: 
                print("Serial connection is closed")
        except Exception as e:
            print(f"Failed to send message: {e}")

    def read(self):
        try:
            if self.isOpen():
                response = self.serial.readline().decode('utf-8').strip()
                print(f"Message read: {response}")
                return response
            else: 
                print("Serial connection is closed")
            
        except Exception as e:
            print(f"Failed to send message: {e}")
            return None
        return None
    
    def __del__(self):
        self.close()


serialComm = SerialCommunication(settings.SERIAL_PORT, settings.SERIAL_BAUDRATE)

def getSerialComm():
    global serialComm
    if not serialComm.isOpen():
        print("Serial is closed, attempting to open...")
        try:
            serialComm.open()
        except serial.SerialException as e:
            print(f"SerialException while opening the port: {e}")
        except PermissionError as e:
            print(f"PermissionError while opening the port: {e}. Retrying...")
            time.sleep(2)  # Attendi prima di riprovare
            try:
                serialComm.open()
            except Exception as e:
                print(f"Failed to open the port after retry: {e}")
                return None  # Restituisci None se non riesci ad aprire la porta

    if serialComm.isOpen():
        print("Serial port successfully opened.")
        return serialComm
    else:
        print("Failed to open serial port.")
        return None