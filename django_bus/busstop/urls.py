from django.urls import path
from busstop import views
from django.conf.urls.static import static
from django.conf import settings

app_name = "busstop"

urlpatterns = [

   path('search/', views.search_busstop_by_name),
   path('feed/', views.feed),

]
