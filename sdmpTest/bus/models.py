from django.db import models


# Create your models here.


class BusIndeBaseModel(models.Model):
    key = models.CharField(max_length=128, unique=True, db_index=True)
    run_status = models.PositiveSmallIntegerField(default=0, verbose_name='运行状态') # 运行状态 选项：0=正常 1=预警 2=告警 3= 升级 4=故障 5=离线
    apparent_power = models.FloatField(default=0)
    active_power = models.FloatField(default=0)
    power_factor = models.FloatField(default=0)
    total_ele = models.FloatField(default=0)
    current_alarm = models.CharField(max_length=256, null=True, verbose_name='当前报警')
    createtime = models.DateTimeField(auto_now_add=True)
    updatetime = models.DateTimeField(auto_now=True)
    class Meta:
        abstract = True


class BusDataBaseModel(models.Model):
    # 0:统计 1:相 2:回路 3:插接位 4:线 6:环境
    type = models.PositiveSmallIntegerField(default=0)
    # 1:断路器 2:电压 3:电流 4:有功功率 5:电能 6:功率因素 7:视在功率 8:无功功率
    # 9:谐波含量 10:负载百分比 11:温度 12:三相不平衡 21:剩余电流 22:零线电流
    topic = models.PositiveSmallIntegerField(default=0)
    indexes = models.PositiveSmallIntegerField(default=0)
    value = models.FloatField(default=0)
    createtime = models.DateTimeField(auto_now_add=True)
    class Meta:
        abstract = True

class BusAlarmBaseModel(models.Model):
    alarm_status = models.CharField(max_length=64, blank=True, null=True, verbose_name='报警类型')
    alarm_content = models.CharField(max_length=128, blank=True, null=True, verbose_name='报警内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')

    class Meta:
        abstract = True

class BusEventBaseModel(models.Model):
    event_type = models.CharField(max_length=64, blank=True, null=True, verbose_name='事件类型')
    event_content = models.CharField(max_length=128, blank=True, null=True, verbose_name='事件内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')

    class Meta:
        abstract = True

class BusUutBaseModel(models.Model):
    dev_sn = models.CharField(max_length=64, null=True, verbose_name='序列号')
    dev_type = models.CharField(max_length=64, null=True, verbose_name='设备型号')
    idc_name = models.CharField(max_length=64, null=True, verbose_name='数据中心')
    room_name = models.CharField(max_length=64, null=True, verbose_name='机房名称')
    cabinet_name = models.CharField(max_length=64, null=True, verbose_name='机柜名称')
    dev_position = models.CharField(max_length=64, null=True, verbose_name='设备位置')
    qrcode = models.CharField(max_length=256, null=True, verbose_name='二维码内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')
    class Meta:
        abstract = True

