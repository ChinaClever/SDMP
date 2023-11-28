from django.db import models
from pdu.index.models import PduIndexModel

class PduEventModel(models.Model):
    """PDU事件记录表"""
    class Meta: db_table = 'pdu_event'
    pdu = models.ForeignKey(to=PduIndexModel, on_delete=models.CASCADE)  # 一对多
    event_type = models.CharField(max_length=64, blank=True, null=True, verbose_name='事件类型')
    event_content = models.CharField(max_length=128, blank=True, null=True, verbose_name='事件内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')

