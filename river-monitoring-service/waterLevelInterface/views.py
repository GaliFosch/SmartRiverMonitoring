from datetime import timedelta
from django.utils import timezone
import json
from django.http import JsonResponse
from .mqtt import client as mqtt_client


def publish_message(request):
    request_data = json.loads(request.body)
    rc, mid = mqtt_client.publish(request_data['topic'], request_data['msg'])
    return JsonResponse({'code': rc})

def recentMeasurements(request):
    from .models import Measurement
    oneHourAgo = timezone.now() - timedelta(hours=1)
    recentMeasurements = Measurement.objects.filter(timestamp__gte=oneHourAgo)
    data = [
        {
            "value": measurement.value,
            "timestamp": measurement.timestamp
        }
        for measurement in recentMeasurements
    ]

    return JsonResponse(data, safe=False)
