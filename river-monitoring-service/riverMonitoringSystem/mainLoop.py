import threading
import time
from enum import Enum, unique
from django.conf import settings
from waterLevelInterface.mqtt import signalFrequenceChange
from waterLevelInterface.mqtt import getLastMeasurment

from gateInterface.serialComm import getSerialComm

@unique
class States(Enum):
    NORMAL = "NORMAL"
    ALARM_TOO_LOW = "ALARM-TOO-LOW"
    PRE_ALARM_TOO_HIGH = "PRE-ALARM-TOO-HIGH"
    ALARM_TOO_HIGH = "ALARM-TOO-HIGH"
    ALARM_TOO_HIGH_CRITIC = "ALARM-TOO-HIGH-CRITIC"

state = States.NORMAL

def getState():
    global state
    return state

def loop():
    global state
    stateChange = True
    serial = getSerialComm()
    serial.open()
    time.sleep(20)
    while True:
        measurement = getLastMeasurment()
        if state == States.NORMAL:
            if stateChange:
                stateChange = False
                print("Normal")
                signalFrequenceChange(settings.F1)
                #Set opening of the gate to 25%
                serial.storeMessage("25")
            if measurement < settings.WL1:
                state = States.ALARM_TOO_LOW
                stateChange = True
            if measurement > settings.WL2:
                state = States.PRE_ALARM_TOO_HIGH
                stateChange = True
        elif state == States.ALARM_TOO_LOW:
            if stateChange:
                stateChange = False
                print("Alarm_tooLow")
                #Set opening of the gate to 0%
                serial.storeMessage("0")
            if measurement >= settings.WL1:
                state = States.NORMAL
                stateChange = True
        elif state == States.PRE_ALARM_TOO_HIGH:
            if stateChange:
                stateChange = False
                print("pre_alarm_too_high")
                signalFrequenceChange(settings.F2)
            if measurement <= settings.WL2:
                state = States.NORMAL
                stateChange = True
            if measurement > settings.WL3:
                state = States.ALARM_TOO_HIGH
                stateChange = True
        elif state == States.ALARM_TOO_HIGH:
            if stateChange:
                stateChange = False
                print("alarm_too_high")
                #Set opening of the gate to 50%
                serial.storeMessage("50")
            if measurement <= settings.WL3:
                state = States.ALARM_TOO_HIGH
                stateChange = True
            if measurement > settings.WL4:
                state = States.ALARM_TOO_HIGH_CRITIC
                stateChange = True
        elif state == States.ALARM_TOO_HIGH_CRITIC:
            if stateChange:
                stateChange = False
                print("alarm_too_high_crit")
                #Set opening of the gate to 100%
                serial.storeMessage("100")
            if measurement <= settings.WL4:
                state = States.ALARM_TOO_HIGH
                stateChange = True
        serial.open()
        serial.sendStoredMessage()
        serial.readAndStore()
        time.sleep(5)
    

main_loop_thread = None

def startMainLoop():
    global main_loop_thread

    if main_loop_thread and main_loop_thread.is_alive():
        print("Main loop is already running.")
        return main_loop_thread

    print("Starting main loop...")
    main_loop_thread = threading.Thread(target=loop, daemon=True)
    main_loop_thread.start()
    return main_loop_thread