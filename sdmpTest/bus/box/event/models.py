from django.db import models
from bus.models import BusEventBaseModel
from bus.box.index.models import BoxIndexModel

class BoxEventModel(BusEventBaseModel):
    class Meta: db_table = 'bus_box_event'
    box = models.ForeignKey(to=BoxIndexModel, on_delete=models.CASCADE)  # 一对多
