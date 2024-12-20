import json
from django.conf import settings
from django.http import JsonResponse
from django.shortcuts import render

from serialComm import serial_read, serial_send

def setOpeningValue(request):
    rc = 400
    if request.method == "GET":
        value = request.GET.get('value', '')
        serial_send(settings.SERIAL_PORT, settings.BAUDRATE, f"set:{value}")
        rc = 200
    return JsonResponse({'errorCode': rc})

def readUpdateMsg(request):
    error = 1
    state = ""
    openingValue = 0

    message = serial_read()
    if message != -1:
        try:
            data = json.loads(message)
            if "state" in data and "opVal" in data:
                state = data["state"]
                openingValue = data["opVal"]
                error = 0
        except json.JSONDecodeError:
            print("JSONDecodeError")

   
    return JsonResponse(
        {
            'errorCode': error,
            'state': state,
            'opVal': openingValue
        }
    )
