from django.urls import path

from . import views

urlpatterns = [
    path("publish", views.publish_message, name="publish"),
    path("recentMeasurments", views.recentMeasurments, name="recentMeasurments")
]