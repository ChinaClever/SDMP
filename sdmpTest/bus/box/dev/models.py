from django.db import models
from bus.box.index.models import BoxIndexModel


class BoxDevModel(models.Model):
    class Meta: db_table = 'bus_box_dev'
    box = models.OneToOneField(to=BoxIndexModel, unique=True, on_delete=models.CASCADE)  # 一对多
    line_num = models.PositiveSmallIntegerField(default=1, verbose_name='相数量')  # 相数量 1=单相，3=三相
    loop_num = models.PositiveSmallIntegerField(default=0, verbose_name='回路数量')  # 回路数量 1 - 6
    outlet_num = models.PositiveSmallIntegerField(default=0, verbose_name='插接位数量')
    dev_addr = models.PositiveSmallIntegerField(default=0, verbose_name='设备地址')
    dev_spec = models.PositiveSmallIntegerField(default=0, verbose_name='电流规格')  # 0：标准  1：250A	1：400A  2：650A
    dev_mode = models.PositiveSmallIntegerField(default=0, verbose_name='设备模式')  # 0：有线 1：无线
    com_baud = models.PositiveSmallIntegerField(default=0, verbose_name='波特率')  # 1：9600  2：19200   3：38400   4：57600
    custom_made = models.PositiveSmallIntegerField(default=0, verbose_name='项目ID')  # 0：标准  1:定制
    alarm_filter = models.PositiveSmallIntegerField(default=0, verbose_name='告警滤波')  # 连续2-5次
    iof_module = models.PositiveSmallIntegerField(default=0, verbose_name='iOF触点')  # 0：没有  1：有
    buzzer = models.PositiveSmallIntegerField(default=0, verbose_name='蜂鸣器')  # 0：开启  1：关闭
    sw_version = models.CharField(max_length=64, null=True, verbose_name='软件版本')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')

