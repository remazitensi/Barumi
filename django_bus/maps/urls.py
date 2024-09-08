from django.urls import path
from maps import views
from django.conf.urls.static import static
from django.conf import settings

app_name = "maps"

urlpatterns = [
                  path('navigation/', views.show_navigation),
                  path('search/', views.search_place),
                  path('test/', views.test),
                  path('', views.main),
                  path('main', views.main_ta_bus),


              ]
