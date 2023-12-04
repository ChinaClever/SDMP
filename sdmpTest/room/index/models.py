
from django.db import models

# Create your models here.


class RoomIndexModel(models.Model):
    class Meta: db_table = 'room_index'
    id = models.AutoField(primary_key=True)
    idc_id = models.IntegerField(default=0, db_index=True)
    room_name = models.CharField(max_length=256, null=False, verbose_name='机房名称')
    cabinet_num = models.PositiveSmallIntegerField(default=0, verbose_name='机柜数量')
    location = models.CharField(max_length=64, null=True, verbose_name='位置')
    createtime = models.DateTimeField(auto_now_add=True)
    updatetime = models.DateTimeField(auto_now=True)


