from threading import Lock
import time
import serial
from django.conf import settings

serialComm = None

def initSerialComm():
    global serialComm
    serialComm = SerialCommunication(settings.SERIAL_PORT, settings.SERIAL_BAUDRATE)

def getSerialComm():
    global serialComm
    return serialComm

class SerialCommunication:
    
    def __init__(self, port: str, baudrate: int, timeout: float = 1):
        self.serial = None
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout
        self.lastMessageRead = None
        self.lock = Lock()
        self.nextMessage = None
    
    def open(self):
        if self.serial is None:
            try:
                self.serial = serial.Serial(
                    port=self.port,
                    baudrate=self.baudrate,
                    timeout=self.timeout
                )
                self.serial.dtr = False
            except Exception as e:
                print(f"Error:{e}")
        elif self.serial.is_open:
            try:
                self.serial.open()
            except Exception as e:
                print(f"Error:{e}")
        
    def isOpen(self):
        return self.serial is not None and self.serial.is_open
    
    def storeMessage(self, message: str):
        with self.lock:
            self.nextMessage = message

    def sendStoredMessage(self):
        if self.isOpen() and self.nextMessage is not None:
            message = self.nextMessage
            try:
                if not message.endswith('\n'):
                    message += '\n'
                self.serial.write(message.encode())
                print(f"Message sent: {message.strip()}")
                self.nextMessage = None
            except Exception as e:
                print(f"Failed to send message: {e}")

    def read(self):
        if self.isOpen() and self.serial.in_waiting > 0: 
            try:
                response = self.serial.readline().decode('utf-8').strip()
                print(f"Message read: {response}")
                return response
            except Exception as e:
                print(f"Failed to read message: {e}")
        return None
    
    def readAndStore(self):
        msg = self.read()
        if msg is not None:
            self.lastMessageRead = msg
    
    def getLastMessageRead(self):
        return self.lastMessageRead

    def __del__(self):
        self.serial.close()