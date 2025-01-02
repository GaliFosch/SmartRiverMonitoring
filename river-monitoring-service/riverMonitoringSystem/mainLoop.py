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
stateChange = True
gateValueToSend = True

def getState():
    global state
    return state

def loop():
    global state
    global stateChange
    global gateValueToSend
    time.sleep(5)
    while True:
        measurement = getLastMeasurment()
        print(measurement)
        if state == States.NORMAL:
            if stateChange:
                stateChange = False
                print("Normal")
                signalFrequenceChange(settings.F1)
            if gateValueToSend:
                serial = getSerialComm()
                if serial:
                    #Set opening of the gate to 25%
                    serial.send("25")
                    gateValueToSend = False
            if measurement < settings.WL1:
                stateChange = True
                state = States.ALARM_TOO_LOW
            if measurement > settings.WL2:
                stateChange = True
                state = States.PRE_ALARM_TOO_HIGH
        elif state == States.ALARM_TOO_LOW:
            if stateChange:
                stateChange = False
                print("Alarm_tooLow")
            if gateValueToSend:
                serial = getSerialComm()
                if serial:
                    #Set opening of the gate to 0%
                    serial.send("0")
                    gateValueToSend = False
            if measurement >= settings.WL1:
                stateChange = True
                state = States.NORMAL
        elif state == States.PRE_ALARM_TOO_HIGH:
            if stateChange:
                stateChange = False
                print("pre_alarm_too_high")
                signalFrequenceChange(settings.F2)
            if measurement <= settings.WL2:
                stateChange = True
                state = States.NORMAL
            if measurement > settings.WL3:
                stateChange = True
                state = States.ALARM_TOO_HIGH
        elif state == States.ALARM_TOO_HIGH:
            if stateChange:
                stateChange = False
                print("alarm_too_high")
            if gateValueToSend:
                serial = getSerialComm()
                if serial:
                    #Set opening of the gate to 50%
                    serial.send("50")
                    gateValueToSend = False
            if measurement <= settings.WL3:
                stateChange = True
                state = States.PRE_ALARM_TOO_HIGH
            if measurement > settings.WL4:
                stateChange = True
                state = States.ALARM_TOO_HIGH_CRITIC
        elif state == States.ALARM_TOO_HIGH_CRITIC:
            if stateChange:
                stateChange = False
                print("alarm_too_high_crit")
            if gateValueToSend:
                serial = getSerialComm()
                if serial:
                    #Set opening of the gate to 100%
                    serial.send("100")
                    gateValueToSend = False
            if measurement <= settings.WL4:
                stateChange = True
                state = States.ALARM_TOO_HIGH
        time.sleep(5)

def changeState(newState: States):
    global state
    global stateChange
    global gateValueToSend
    state = newState
    stateChange = True
    gateValueToSend = True
    

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