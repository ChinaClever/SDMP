
from django.db import models
from cabinet.index.models import CabinetIndexModel
# Create your models here.


class RackIndexModel(models.Model):
    class Meta: db_table = 'rack_index'
    id = models.AutoField(primary_key=True)
    cabinet = models.ForeignKey(to=CabinetIndexModel, on_delete=models.CASCADE)  # 一对多
    rack_name = models.CharField(max_length=128, null=False, verbose_name='机架名称')
    company = models.CharField(max_length=128, null=False, verbose_name='所属公司')
    is_disabled = models.PositiveSmallIntegerField(default=0, verbose_name='禁用')
    u_address = models.PositiveSmallIntegerField(default=0, verbose_name='U位位置')
    u_height = models.PositiveSmallIntegerField(default=42, verbose_name='U位高度')
    a_port = models.PositiveSmallIntegerField(default=0, verbose_name='A路端口号')
    b_port = models.PositiveSmallIntegerField(default=0, verbose_name='B路端口号')
    remarks = models.CharField(max_length=256, null=True, verbose_name='备注')
    createtime = models.DateTimeField(auto_now_add=True)
    updatetime = models.DateTimeField(auto_now=True)

