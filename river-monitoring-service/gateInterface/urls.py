from django.urls import path

from . import views

urlpatterns = [
    path("setOpeningLevel", views.setOpeningValue, name="setOpeningLevel"),
    path("readUpdateMsg", views.readUpdateMsg, name="readUpdateMsg")
]