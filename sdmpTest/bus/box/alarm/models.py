from django.db import models
from bus.models import BusAlarmBaseModel
from bus.box.index.models import BoxIndexModel



class BoxAlarmModel(BusAlarmBaseModel):
    class Meta: db_table = 'bus_box_alarm'
    box = models.ForeignKey(to=BoxIndexModel, on_delete=models.CASCADE)  # 一对多