from django.conf import settings
import paho.mqtt.client as mqtt
import json

lastMeasurement = -10000

def getLastMeasurment():
    global lastMeasurement
    if(lastMeasurement <= -10000):
        from .models import Measurement
        lastMeasurement = Measurement.objects.latest("timestamp").value
    return lastMeasurement

def on_connect(mqtt_client, userdata, flags, rc):
    if rc == 0:
        print('Connected successfully')
        mqtt_client.subscribe('SRM/waterlevel')
    else:
        print('Bad connection. Code:', rc)

def on_message(mqtt_client, userdata, msg):
    from .models import Measurement
    global lastMeasurement
    try:
        data = json.loads(msg.payload.decode())
        if data[0] == "VALUE":
            if 'value' in data[1] and isinstance(data[1]["value"], float):
                lastMeasurement = data[1]['value']
                
                measurement = Measurement(value=lastMeasurement)
                measurement.save()
            else:
                print("ERROR: received non-numeric data")
    except json.JSONDecodeError as e:
        print("ERROR: JSON decoding failed:", e)
    except Exception as e:
        print("ERROR: An unexpected error occurred:", e)
    
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.username_pw_set(settings.MQTT_USER, settings.MQTT_PASSWORD)
client.connect(
    host=settings.MQTT_SERVER,
    port=settings.MQTT_PORT,
    keepalive=settings.MQTT_KEEPALIVE
)

def signalFrequenceChange(frequency):
    result = client.publish("SRM/waterlevel", "[ \"FREQ\"," + str(frequency) + "]")
    result.wait_for_publish()
