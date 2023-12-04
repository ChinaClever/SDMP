from room.index.models import RoomIndexModel
from django.db import models
from decimal import Decimal

class RoomHdaModel(models.Model):
    class Meta: db_table = 'room_hda'
    room = models.ForeignKey(to=RoomIndexModel, on_delete=models.CASCADE)  # 一对多
    apparent_power = models.DecimalField(default=Decimal('0.000'), max_digits=10, decimal_places=3)
    active_power = models.DecimalField(default=Decimal('0.000'), max_digits=10, decimal_places=3)
    power_factor = models.DecimalField(default=Decimal('0.00'), max_digits=4, decimal_places=2)
    total_ele = models.DecimalField(default=Decimal('0.0'), max_digits=10, decimal_places=1)
    createtime = models.DateTimeField(auto_now_add=True)
