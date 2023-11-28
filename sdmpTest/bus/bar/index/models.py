from django.db import models
from bus.models import BusIndeBaseModel

# Create your models here.

class BarIndexModel(BusIndeBaseModel):
    class Meta: db_table = 'bus_bar_index'
    zero_line_current = models.FloatField(default=0)
    voltage_unbalance = models.FloatField(default=0)
    current_unbalance = models.FloatField(default=0)
    breaker_status = models.PositiveSmallIntegerField(default=0)
    hz = models.PositiveSmallIntegerField(default=0, verbose_name='频率')
    ip_addr = models.PositiveSmallIntegerField(default=2, verbose_name='设备地址')
    box_num = models.PositiveSmallIntegerField(default=3, verbose_name='插接箱数量')

