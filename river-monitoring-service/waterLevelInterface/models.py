from django.db import models

# Create your models here.
class Measurment(models.Model):
    value = models.FloatField()
    timestamp = models.DateTimeField(auto_now_add=True)