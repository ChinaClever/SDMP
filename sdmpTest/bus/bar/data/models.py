from django.db import models
from bus.models import BusDataBaseModel
from bus.bar.index.models import BarIndexModel


class BarDataModel(BusDataBaseModel):
    class Meta: db_table = 'bus_bar_data'
    bar = models.ForeignKey(to=BarIndexModel, on_delete=models.CASCADE)
    updatetime = models.DateTimeField(auto_now=True)


