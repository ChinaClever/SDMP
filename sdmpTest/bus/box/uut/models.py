from django.db import models
from bus.models import BusUutBaseModel
from bus.box.index.models import BoxIndexModel

class BoxUutModel(BusUutBaseModel):
    class Meta: db_table = 'bus_box_uut'
    box = models.OneToOneField(to=BoxIndexModel, unique=True, on_delete=models.CASCADE)  # 一对

