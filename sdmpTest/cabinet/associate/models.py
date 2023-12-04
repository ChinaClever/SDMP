from cabinet.index.models import CabinetIndexModel
from django.db import models


class CabinetPduModel(models.Model):
    class Meta: db_table = 'cabinet_pdu'
    cabinet = models.OneToOneField(to=CabinetIndexModel, on_delete=models.CASCADE)
    a_pdu_id = models.IntegerField(default=0)
    b_pdu_id = models.IntegerField(default=0)
    createtime = models.DateTimeField(auto_now_add=True)
    updatetime = models.DateTimeField(auto_now=True)


class CabinetBoxModel(models.Model):
    class Meta: db_table = 'cabinet_box'
    cabinet = models.OneToOneField(to=CabinetIndexModel, on_delete=models.CASCADE)
    a_box_id = models.IntegerField(default=0)
    a_box_outlet = models.PositiveSmallIntegerField(default=0)
    b_box_id = models.IntegerField(default=0)
    b_box_outlet = models.PositiveSmallIntegerField(default=0)
    createtime = models.DateTimeField(auto_now_add=True)
    updatetime = models.DateTimeField(auto_now=True)