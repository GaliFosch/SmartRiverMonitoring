from serialComm import SerialCommunication
import time

SerialCommunication("COM17").open()

SerialCommunication("COM17").send("45")
time.sleep(10)
SerialCommunication("COM17").send("20")