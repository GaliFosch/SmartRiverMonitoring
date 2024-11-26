import json
from django.http import HttpResponse
from django.utils import timezone
from waterLevelInterface.models import Measurement
import sqlite3
import datetime

def get_data(request):
    timeNow = datetime.datetime.now(tz=timezone.utc).replace(microsecond=0)
    tenMinutesAgo = timeNow - datetime.timedelta(minutes=10)
    
    # sends back the water levels of the past 10 minutes
    conn = sqlite3.connect('db.sqlite3')
    cursor = conn.cursor()
    
    # query
    query = "SELECT * FROM waterLevelInterface_measurement LIMIT 30"
    cursor.execute(query)
    # query = "SELECT * FROM waterLevelInterface_measurement WHERE timestamp >= ?"
    # cursor.execute(query, (tenMinutesAgo.strftime('%Y-%m-%d %H:%M:%S'),))
    rows = cursor.fetchall()
    
    # set up conversion to json
    col_names = [desc[0] for desc in cursor.description]
    json_obj = []
    for row in rows:
        row_dict = dict(zip(col_names, row))
        json_obj.append(row_dict)

    response = HttpResponse(json.dumps(json_obj), content_type="application/json")
    return response
    
