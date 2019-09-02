from django.urls import path
from . import views

app_name = 'FastQuery'

urlpatterns = [

    path('', views.DashboardView.as_view(), name = 'Dashboard'),
    path('dataset', views.DatasetView.as_view(), name = 'Dataset'),
    path('download', views.DownloadView.as_view(), name = 'Download'),
    path('query', views.QueryView.as_view(), name = 'Query'),
    path('query1', views.Query1View.as_view(), name = 'Query1'),
    path('query2', views.Query2View.as_view(), name = 'Query2'),
    path('query3', views.Query3View.as_view(), name = 'Query3'),
    path('naive', views.NaiveView.as_view(), name = 'Naive'),

]
