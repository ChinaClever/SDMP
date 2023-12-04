from django.db import models
from pdu.index.models import PduIndexModel


class PduThresholdModel(models.Model):
    """PDU实时数据表"""
    class Meta: db_table = 'pdu_threshold'
    pdu = models.ForeignKey(to=PduIndexModel, on_delete=models.CASCADE)  # 一对多

    # 1=相数据 2=回路数据 3=输出位数据 4=分组数据 5=机架数据 6=环境（温湿度）
    # 7=传感器（门禁其他传感器）  0=统计数据（总功率，总电能）
    type = models.PositiveSmallIntegerField(default=0)

    # 1：开关 2：电压 3：电流 4：功率 5：电能 6：功率因数 7：视在功率 8：无功功率 9：电能记录
    # 10、线电压 11：温度 12：湿度 21：门禁1 22：门禁2 23：水禁 24：烟雾
    topic = models.PositiveSmallIntegerField(default=0)

    # 1：当前值（开关状态） 2：额定值 （断开告警） 3：报警状态 4：最大值（上电延时） 5：最小值（复位延时）
    # 6：下临界值（超限断电） 7：上临界值（定时开关） 8：使能状态（开关关键设备保护） 9：最大峰值（开关当前次数）
    subtopic = models.PositiveSmallIntegerField(default=0)
    indexes = models.PositiveSmallIntegerField(default=0)
    value = models.FloatField(default=0)
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')