from threading import Lock
import time
import serial

class SerialCommunication:
    _instance = None
    _lock = Lock()  # Lock per garantire thread-safety

    def __new__(cls, *args, **kwargs):
        if not cls._instance:
            with cls._lock:
                if not cls._instance:
                    cls._instance = super().__new__(cls)
        return cls._instance
    
    def __init__(self, port = None, baudrate = 9600, timeout = 1):
        if not hasattr(self, 'initialized'):
            if port is None: 
                raise ValueError("Port is not setted")
            self.port = port
            self.baudrate = baudrate
            self.timeout = timeout
            self.serial = None
            self.lock = Lock()
            self.initialized = True

    def open(self):
        print(self.serial)
        try:
            self.serial = serial.Serial(
                port = self.port, 
                baudrate = self.baudrate, 
                timeout = self.timeout
                )
            self.serial.drt = False
            time.sleep(2)
            print(f"Open Connection on port {self.port} with baudrate {self.baudrate}.")
        except Exception as e:
            print(f"Error in serial connection: {e}")
    
    def close(self):
        if self.isOpen():
            self.serial.close()
            print("Serial Connection closed")

    def isOpen(self):
        return self.serial is not None and self.serial.is_open

    def send(self, message):
        try:

            if not message.endswith('\n'):
                message += '\n'

            self.serial.write(message.encode())
            print(f"Message sent: {message.strip()}")
        except Exception as e:
            print(f"Failed to send message: {e}")

    def read(self):
        try:
            response = self.serial.readline().decode('utf-8').strip()
            print(f"Message read: {response}")
            return response
            
        except Exception as e:
            print(f"Failed to send message: {e}")
            return None
        return None
    
    def __del__(self):
        print("deleted")
        self.close()
