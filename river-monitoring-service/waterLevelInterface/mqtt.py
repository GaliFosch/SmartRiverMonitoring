from django.conf import settings
import paho.mqtt.client as mqtt
import json

lastMeasurment = 0

def on_connect(mqtt_client, userdata, flags, rc):
    if rc == 0:
        print('Connected successfully')
        mqtt_client.subscribe('SRM/waterlevel')
    else:
        print('Bad connection. Code:', rc)

def on_message(mqtt_client, userdata, msg):
    from .models import Measurment
    global lastMeasurment
    try:
        data = json.loads(msg.payload.decode())
        
        if 'value' in data and isinstance(data['value'], (int, float)):
            lastMeasurment = data['value']
            
            measurment = Measurment(value=lastMeasurment)
            measurment.save()
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
    return client.publish("RMS/waterlevel/frequency", str(frequency))