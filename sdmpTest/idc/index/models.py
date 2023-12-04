
from django.db import models

# Create your models here.


class IdcIndexModel(models.Model):
    class Meta: db_table = 'idc_index'
    id = models.AutoField(primary_key=True)
    idc_name = models.CharField(max_length=256, null=False, verbose_name='IDC名称')
    createtime = models.DateTimeField(auto_now_add=True)
    updatetime = models.DateTimeField(auto_now=True)

