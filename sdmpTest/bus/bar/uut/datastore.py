from datetime import datetime
from django.db import transaction
from bus.bar.uut.models import BarUutModel
from bus.bar.index.datastore import BarIndexStore
from typing import Dict





class BarUutStore:
    def __init__(self):
        self.objects: Dict[int, BarUutModel] = {}
        self.objects = {obj.bar_id: obj for obj in BarUutModel.objects.all()}

    def uut_saves(self):
        with transaction.atomic():
            for obj in self.objects.values():
                    obj.save()

    def uut_obj(self, bar_id: int) -> BarUutModel:
        obj = self.objects.get(bar_id)
        if obj is None:
            obj = BarUutModel(bar_id=bar_id)
            self.objects[bar_id] = obj
        return obj


    def uut_update(self, key):
        bar_id = BarIndexStore.index_id(key)
        obj = self.uut_obj(bar_id)

        obj.idc_name = 'idc'
        obj.room_name = 'room'
        obj.cabinet_name = 'cabinet'