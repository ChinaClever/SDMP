from django.db import models
from bus.models import BusEventBaseModel
from bus.bar.index.models import BarIndexModel

class BarEventModel(BusEventBaseModel):
    class Meta: db_table = 'bus_bar_event'
    bar = models.ForeignKey(to=BarIndexModel, on_delete=models.CASCADE)  # 一对多
