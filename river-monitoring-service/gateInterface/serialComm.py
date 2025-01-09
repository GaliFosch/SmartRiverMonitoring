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

    def sendStoredMessage(self, maxTries=1):
        tries = 0
        while tries<maxTries:
            if self.isOpen() and self.nextMessage is not None:
                message = self.nextMessage
                try:
                    if not message.endswith('\n'):
                        message += '\n'
                    self.serial.write(message.encode())
                    print(f"Message sent: {message.strip()}")
                    self.nextMessage = None
                    break
                except Exception as e:
                    print(f"Failed to send message: {e}")
            tries += 1
            time.sleep(0.2)

    def _read(self):
        if self.isOpen() and self.serial.in_waiting > 0: 
            try:
                response = self.serial.readline().decode('utf-8').strip()
                print(f"Message read: {response}")
                return response
            except Exception as e:
                print(f"Failed to read message: {e}")
        return None
    
    def readAndStore(self, maxTries: int = 1):
        tries = 0
        while tries<maxTries:
            msg = self._read()
            if msg is not None:
                self.lastMessageRead = msg
                print("saved msg:" + msg)
                break
            tries += 1
            time.sleep(0.2)
    
    def getLastMessageRead(self):
        with self.lock:
            return self.lastMessageRead

    def __del__(self):
        if self.isOpen():
            self.serial.close()