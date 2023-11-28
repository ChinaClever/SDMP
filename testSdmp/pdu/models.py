from django.db import models

# Create your models here.

class PduIndex(models.Model):
    class Meta: db_table = 'pdu_index'
    id = models.AutoField(primary_key=True)
    key = models.CharField(max_length=128, unique=True, db_index=True)
    run_status = models.PositiveSmallIntegerField(default=0, verbose_name='运行状态') # 运行状态 选项：0=正常 1=预警 2=告警 3= 升级 4=故障 5=离线
    apparent_power = models.FloatField(default=0)
    active_power = models.FloatField(default=0)
    power_factor = models.FloatField(default=0)
    total_ele = models.FloatField(default=0)
    ip_addr = models.CharField(max_length=64, null=True, verbose_name='IP地址')
    cascade_addr = models.PositiveSmallIntegerField(default=0, verbose_name='级联地址')
    current_alarm = models.CharField(max_length=256, null=True, verbose_name='当前报警')
    createtime = models.DateTimeField(auto_now_add=True)
    updatetime = models.DateTimeField(auto_now=True)

