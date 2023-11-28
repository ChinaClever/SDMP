from django.db import models
from bus.models import BusUutBaseModel
from bus.bar.index.models import BarIndexModel

class BarUutModel(BusUutBaseModel):
    class Meta: db_table = 'bus_bar_uut'
    bar = models.OneToOneField(to=BarIndexModel, unique=True, on_delete=models.CASCADE)  # 一对
