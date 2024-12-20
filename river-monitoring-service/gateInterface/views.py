import json
from django.conf import settings
from django.http import JsonResponse
from django.shortcuts import render

from serialComm import serial_read, serial_send

def setOpeningValue(request):
    rc = 400
    if request.method == "GET":
        value = request.GET.get('value', '')
        serial_send(settings.SERIAL_PORT, settings.BAUDRATE, f"{value}")
        rc = 200
    return JsonResponse({'errorCode': rc})

def readOpVal(request):
    error = 1
    openingValue = 0

    message = serial_read()
    if message != -1:
        try:
            openingValue = int(message)
            error = 0
        except ValueError:
            print("non int number")
    
    return JsonResponse(
        {
            'errorCode': error,
            'opVal': openingValue
        }
    )
