from rack.index.models import RackIndexModel
from django.db import models
from decimal import Decimal


class RackDataModel(models.Model):
    """实时数据表"""

    class Meta: db_table = 'rack_data'
    rack = models.OneToOneField(to=RackIndexModel, on_delete=models.CASCADE)
    apparent_power = models.DecimalField(default=Decimal('0.000'), max_digits=10, decimal_places=3)
    active_power = models.DecimalField(default=Decimal('0.000'), max_digits=10, decimal_places=3)
    power_factor = models.DecimalField(default=Decimal('0.00'), max_digits=4, decimal_places=2)
    total_ele = models.DecimalField(default=Decimal('0.0'), max_digits=10, decimal_places=1)
    updatetime = models.DateTimeField(auto_now=True)

