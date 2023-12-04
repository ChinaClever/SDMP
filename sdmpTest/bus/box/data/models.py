from django.db import models
from bus.models import BusDataBaseModel
from bus.box.index.models import BoxIndexModel


class BoxDataModel(BusDataBaseModel):
    class Meta: db_table = 'bus_box_data'
    box = models.ForeignKey(to=BoxIndexModel, on_delete=models.CASCADE)
    updatetime = models.DateTimeField(auto_now=True)

