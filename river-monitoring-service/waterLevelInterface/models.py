from django.db import models
from django.utils import timezone
import datetime

# Create your models here.
class Measurement(models.Model):
    value = models.FloatField()
    timestamp = models.DateTimeField()
    
    def save(self, *args, **kwargs):
        # Remove milliseconds
        self.timestamp = datetime.datetime.now(tz=timezone.utc).replace(microsecond=0)
        super(Measurement, self).save(*args, **kwargs)