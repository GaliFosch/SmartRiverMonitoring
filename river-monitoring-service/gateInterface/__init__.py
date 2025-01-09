from .serialComm import getSerialComm, initSerialComm


initSerialComm()

print(f"git: {id(getSerialComm())}")