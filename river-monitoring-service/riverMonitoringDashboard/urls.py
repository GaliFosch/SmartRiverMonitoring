from django.urls import path
from . import views

urlpatterns = [
    path('get-wlevels/', views.get_data, name="get-wlevels")
]
