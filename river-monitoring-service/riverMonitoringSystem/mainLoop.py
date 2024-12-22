import threading
import time
from enum import Enum, unique
from django.conf import settings
from waterLevelInterface.mqtt import signalFrequenceChange
from waterLevelInterface.mqtt import getLastMeasurment

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
    time.sleep(3)
    while True:
        # print(measurement)
        measurement = getLastMeasurment()
        if state == States.NORMAL:
            if stateChange:
                stateChange = False
                print("Normal")
                signalFrequenceChange(settings.F1)
                #Set opening of the gate to 25%
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
                signalFrequenceChange(settings.F1)
                #Set opening of the gate to 0%
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
                signalFrequenceChange(settings.F2)
                #Set opening of the gate to 50%
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
                signalFrequenceChange(settings.F2)
                #Set opening of the gate to 100%
            if measurement <= settings.WL4:
                stateChange = True
                state = States.ALARM_TOO_HIGH
        time.sleep(1)

def startMainLoop():
    thread = threading.Thread(target = loop)
    thread.start()
    return thread