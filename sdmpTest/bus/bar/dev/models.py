from django.db import models
from bus.bar.index.models import BarIndexModel


class BarDevModel(models.Model):
    class Meta: db_table = 'bus_bar_dev'
    bar = models.OneToOneField(to=BarIndexModel, unique=True, on_delete=models.CASCADE)  # 一对多
    dev_addr = models.PositiveSmallIntegerField(default=0, verbose_name='设备地址')
    dev_spec = models.PositiveSmallIntegerField(default=0, verbose_name='电流规格')  # 0：标准  1：250A	1：400A  2：650A
    dev_mode = models.PositiveSmallIntegerField(default=0, verbose_name='设备模式')  # 0：有线 1：无线
    com_baud = models.PositiveSmallIntegerField(default=0, verbose_name='波特率')  # 1：9600  2：19200   3：38400   4：57600
    custom_made = models.PositiveSmallIntegerField(default=0, verbose_name='项目ID')  # 0：标准  1:定制
    alarm_filter = models.PositiveSmallIntegerField(default=0, verbose_name='告警滤波')  # 连续2-5次
    iof_module = models.PositiveSmallIntegerField(default=0, verbose_name='iOF触点')  # 0：没有  1：有
    buzzer = models.PositiveSmallIntegerField(default=0, verbose_name='蜂鸣器')  # 0：开启  1：关闭
    ac_dc = models.PositiveSmallIntegerField(default=0, verbose_name='交直流')  # 0 交流   1 直流
    thunder_module = models.PositiveSmallIntegerField(default=0, verbose_name='防雷模块')  # 0：无  1：配有
    thunder_status = models.PositiveSmallIntegerField(default=0, verbose_name='防雷状态')  # 1：工作正常   2：损坏
    isd_module = models.PositiveSmallIntegerField(default=0, verbose_name='ISD报警触点')  # 0：无  1：配有
    release_module = models.PositiveSmallIntegerField(default=0, verbose_name='分离脱扣器模块')  # 0：无  1：配有
    aftercur_module = models.PositiveSmallIntegerField(default=0, verbose_name='剩余电流监测模块')  # 0：无  1：配有
    auto_addr_en = models.PositiveSmallIntegerField(default=0, verbose_name='自动设置地址开关')
    auto_addr_mode = models.PositiveSmallIntegerField(default=0, verbose_name='自动设置地址模式')
    auto_addr_status = models.PositiveSmallIntegerField(default=0, verbose_name='自动设置地址状态')
    ip_v6 = models.CharField(max_length=64, null=True, verbose_name='ip_v6')
    sw_version = models.CharField(max_length=64, null=True, verbose_name='软件版本')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')