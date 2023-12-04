from django.db import models
from pdu.index.models import PduIndexModel

class PduAlarmModel(models.Model): # PDU报警记录表
    class Meta: db_table = 'pdu_alarm'
    pdu = models.ForeignKey(to=PduIndexModel, on_delete=models.CASCADE)  # 一对多
    alarm_status = models.CharField(max_length=64, blank=True, null=True, verbose_name='报警类型')
    alarm_content = models.CharField(max_length=128, blank=True, null=True, verbose_name='报警内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')


