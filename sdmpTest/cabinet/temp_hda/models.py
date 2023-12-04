from cabinet.index.models import CabinetIndexModel
from django.db import models
from decimal import Decimal


class CabinetTempHdaModel(models.Model):

    class Meta: db_table = 'cabinet_temp_hda'
    cabinet = models.ForeignKey(to=CabinetIndexModel, on_delete=models.CASCADE)
    a_1 = models.DecimalField(default=Decimal('0.0'), max_digits=3, decimal_places=1)
    a_2 = models.DecimalField(default=Decimal('0.0'), max_digits=3, decimal_places=1)
    a_3 = models.DecimalField(default=Decimal('0.0'), max_digits=3, decimal_places=1)
    a_4 = models.DecimalField(default=Decimal('0.0'), max_digits=3, decimal_places=1)
    b_1 = models.DecimalField(default=Decimal('0.0'), max_digits=3, decimal_places=1)
    b_2 = models.DecimalField(default=Decimal('0.0'), max_digits=3, decimal_places=1)
    b_3 = models.DecimalField(default=Decimal('0.0'), max_digits=3, decimal_places=1)
    b_4 = models.DecimalField(default=Decimal('0.0'), max_digits=3, decimal_places=1)
    createtime = models.DateTimeField(auto_now_add=True)



