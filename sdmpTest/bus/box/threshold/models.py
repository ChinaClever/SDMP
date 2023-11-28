from django.db import models
from bus.models import BusDataBaseModel
from bus.box.index.models import BoxIndexModel


class BoxThresholdModel(BusDataBaseModel):
    class Meta: db_table = 'bus_box_threshold'
    box = models.ForeignKey(to=BoxIndexModel, on_delete=models.CASCADE)
    # 1：当前值 2：额定值 3：报警状态 4：最大值 5：最小值 6：下临界值 7：上临界值 8：使能状态
    subtopic = models.PositiveSmallIntegerField(default=0)
    updatetime = models.DateTimeField(auto_now=True)