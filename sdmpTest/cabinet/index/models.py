
from django.db import models

# Create your models here.


class CabinetIndexModel(models.Model):
    class Meta: db_table = 'cabinet_index'
    id = models.AutoField(primary_key=True)
    room_id = models.IntegerField(default=0, db_index=True)
    cabinet_name = models.CharField(max_length=256, null=False, verbose_name='机柜名称')
    pow_capacity = models.PositiveSmallIntegerField(default=6, verbose_name='电力容量（KVA）')
    pdu_box = models.PositiveSmallIntegerField(default=0, verbose_name='数据来源')
    is_disabled = models.PositiveSmallIntegerField(default=0, verbose_name='禁用')
    height = models.PositiveSmallIntegerField(default=42, verbose_name='高度')
    location = models.CharField(max_length=64, null=True, verbose_name='位置')
    group_name = models.CharField(max_length=64, null=True, verbose_name='组名')
    createtime = models.DateTimeField(auto_now_add=True)
    updatetime = models.DateTimeField(auto_now=True)

