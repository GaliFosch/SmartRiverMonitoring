import json
from django.conf import settings
from django.http import JsonResponse
from django.shortcuts import render

from serialComm import serial_send

def setOpeningValue(request):
    rc = 400
    if request.method == "GET":
        value = request.GET.get('value', '')
        serial_send(settings.SERIAL_PORT, settings.BAUDRATE, f"set:{value}")
        rc = 200
    return JsonResponse({'errorCode': rc})