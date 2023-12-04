from django.db import models
from bus.models import BusAlarmBaseModel
from bus.bar.index.models import BarIndexModel

class BarAlarmModel(BusAlarmBaseModel):
    class Meta: db_table = 'bus_bar_alarm'
    bar = models.ForeignKey(to=BarIndexModel, on_delete=models.CASCADE)  # 一对多


