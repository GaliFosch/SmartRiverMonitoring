from django.urls import path
from . import views

urlpatterns = [
    path('get-wlevels/', views.get_data, name="get-wlevels"),
    path('get-state/', views.get_state, name="get-state")
]
