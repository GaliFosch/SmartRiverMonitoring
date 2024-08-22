from django.db import models

class Mesurment(models.Model):
    value = models.DecimalField(max_digits=6, decimal_places=3)
    date = models.DateTimeField()