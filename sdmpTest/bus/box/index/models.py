from django.db import models
from bus.models import BusIndeBaseModel
from bus.bar.index.models import BarIndexModel

# Create your models here.


class BoxIndexModel(BusIndeBaseModel):
    class Meta: db_table = 'bus_box_index'
    bar = models.ForeignKey(to=BarIndexModel, on_delete=models.CASCADE, null=True) # blank=True
    dev_addr = models.PositiveSmallIntegerField(default=2, verbose_name='设备地址')
    outlet_num = models.PositiveSmallIntegerField(default=3, verbose_name='插接位数量')

