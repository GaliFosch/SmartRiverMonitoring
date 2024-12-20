import threading
import time
from enum import Enum, unique
from django.conf import settings
from waterLevelInterface.mqtt import signalFrequenceChange
from waterLevelInterface.mqtt import lastMeasurement

@unique
class States(Enum):
    NORMAL = "NORMAL"
    ALARM_TOO_LOW = "ALARM-TOO-LOW"
    PRE_ALARM_TOO_HIGH = "PRE-ALARM-TOO-HIGH"
    ALARM_TOO_HIGH = "ALARM-TOO-HIGH"
    ALARM_TOO_HIGH_CRITIC = "ALARM-TOO-HIGH-CRITIC"

state = States.NORMAL

def loop():
    global lastMeasurement
    global state
    stateChange = True
    while True:
        if state == States.NORMAL:
            if stateChange:
                stateChange = False
                signalFrequenceChange(settings.F1)
                #Set opening of the gate to 25%
            if lastMeasurement < settings.WL1:
                stateChange = True
                state = States.ALARM_TOO_LOW
            if lastMeasurement > settings.WL2:
                stateChange = True
                state = States.PRE_ALARM_TOO_HIGH
        elif state == States.ALARM_TOO_LOW:
            if stateChange:
                stateChange = False
                signalFrequenceChange(settings.F1)
                #Set opening of the gate to 0%
            if lastMeasurement >= settings.WL1:
                stateChange = True
                state = States.NORMAL
        elif state == States.PRE_ALARM_TOO_HIGH:
            if stateChange:
                stateChange = False
                signalFrequenceChange(settings.F2)
            if lastMeasurement <= settings.WL2:
                stateChange = True
                state = States.NORMAL
            if lastMeasurement > settings.WL3:
                stateChange = True
                state = States.ALARM_TOO_HIGH
        elif state == States.ALARM_TOO_HIGH:
            if stateChange:
                stateChange = False
                signalFrequenceChange(settings.F2)
                #Set opening of the gate to 50%
            if lastMeasurement <= settings.WL3:
                stateChange = True
                state = States.PRE_ALARM_TOO_HIGH
            if lastMeasurement > settings.WL4:
                stateChange = True
                state = States.ALARM_TOO_HIGH_CRITIC
        elif state == States.ALARM_TOO_HIGH_CRITIC:
            if stateChange:
                stateChange = False
                signalFrequenceChange(settings.F2)
                #Set opening of the gate to 100%
            if lastMeasurement <= settings.WL4:
                stateChange = True
                state = States.ALARM_TOO_HIGH
        time.sleep(0.2)

def StartMainLoop():
    thread = threading.Thread(target = loop)
    thread.start()
    return thread