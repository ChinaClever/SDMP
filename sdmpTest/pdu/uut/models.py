from django.db import models
from pdu.index.models import PduIndexModel


class PduUutModel(models.Model):
    class Meta: db_table = 'pdu_uut'
    id = models.AutoField(primary_key=True)
    pdu = models.OneToOneField(to=PduIndexModel, unique=True, on_delete=models.CASCADE) # 一对一
    dev_sn = models.CharField(max_length=64, null=True, verbose_name='序列号')
    dev_type = models.CharField(max_length=64, null=True, verbose_name='设备型号')
    idc_name = models.CharField(max_length=64, null=True, verbose_name='数据中心')
    room_name = models.CharField(max_length=64, null=True, verbose_name='机房名称')
    cabinet_name = models.CharField(max_length=64, null=True, verbose_name='机柜名称')
    dev_position = models.CharField(max_length=64, null=True, verbose_name='设备位置')
    qrcode = models.CharField(max_length=256, null=True, verbose_name='二维码内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')


