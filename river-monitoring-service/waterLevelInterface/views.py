from datetime import timedelta
from django.utils import timezone
import json
from django.http import JsonResponse
from .mqtt import client as mqtt_client


def publish_message(request):
    request_data = json.loads(request.body)
    rc, mid = mqtt_client.publish(request_data['topic'], request_data['msg'])
    return JsonResponse({'code': rc})

def recentMeasurments(request):
    from .models import Measurment
    oneHourAgo = timezone.now() - timedelta(hours=1)
    recentMeasurments = Measurment.objects.filter(timestamp__gte=oneHourAgo)
    data = [
        {
            "value": measurment.value,
            "timestamp": measurment.timestamp
        }
        for measurment in recentMeasurments
    ]

    return JsonResponse(data, safe=False)
