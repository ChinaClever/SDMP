from django.db import models
from bus.models import BusDataBaseModel
from bus.bar.index.models import BarIndexModel

class BarHdaModel(BusDataBaseModel):
    class Meta: db_table = 'bus_bar_hda'
    bar = models.ForeignKey(to=BarIndexModel, on_delete=models.CASCADE)




