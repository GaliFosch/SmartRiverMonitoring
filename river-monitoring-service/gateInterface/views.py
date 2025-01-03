import json
from django.conf import settings
from django.http import JsonResponse
from django.shortcuts import render
from .serialComm import getSerialComm

def setOpeningValue(request):
    rc = 400
    if request.method == "GET":
        value = request.GET.get('value', '')
        getSerialComm().storeMessage(f"{value}")
        rc = 200
    return JsonResponse({'errorCode': rc})

def readOpVal(request):
    error = 1
    openingValue = 0

    message = getSerialComm().getLastMessageRead()
    if message != None:
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
