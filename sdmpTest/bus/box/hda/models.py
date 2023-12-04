from django.db import models
from bus.models import BusDataBaseModel
from bus.box.index.models import BoxIndexModel

class BoxHdaModel(BusDataBaseModel):
    class Meta: db_table = 'bus_box_hda'
    box = models.ForeignKey(to=BoxIndexModel, on_delete=models.CASCADE)




