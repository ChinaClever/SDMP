from django.db import models
from pdu.index.models import PduIndexModel

class PduDevModel(models.Model):
    class Meta:db_table = 'pdu_dev'
    id = models.AutoField(primary_key=True)
    pdu = models.OneToOneField(to=PduIndexModel, unique=True, on_delete=models.CASCADE) # 一对一
    dev_type = models.CharField(max_length=64, null=True, verbose_name='设备型号')
    dev_spec = models.PositiveSmallIntegerField(default=0, verbose_name='设备规格') # 设备规格 1=A系列，2=B系列，3=C系列，4=D系列，
    dev_mode = models.PositiveSmallIntegerField(default=0, verbose_name='设备模式') # 设备模式 0：标准 1：级联 2：机架
    line_num = models.PositiveSmallIntegerField(default=1, verbose_name='相数量') # 相数量 1=单相，3=三相
    loop_num = models.PositiveSmallIntegerField(default=0, verbose_name='回路数量') # 回路数量 1 - 6
    output_num = models.PositiveSmallIntegerField(default=0, verbose_name='输出位数量')
    sw_version = models.CharField(max_length=64, null=True, verbose_name='软件版本')
    ip_v6 = models.CharField(max_length=64, null=True, verbose_name='ip_v6')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')
