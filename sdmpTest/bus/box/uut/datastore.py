from datetime import datetime
from django.db import transaction
from bus.box.uut.models import BoxUutModel
from bus.box.index.datastore import BoxIndexStore
from typing import Dict





class BoxUutStore:
    def __init__(self):
        self.objects: Dict[int, BoxUutModel] = {}
        self.objects = {obj.box_id: obj for obj in BoxUutModel.objects.all()}

    def uut_saves(self):
        with transaction.atomic():
            for obj in self.objects.values():
                    obj.save()

    def uut_obj(self, box_id: int) -> BoxUutModel:
        obj = self.objects.get(box_id)
        if obj is None:
            obj = BoxUutModel(box_id=box_id)
            self.objects[box_id] = obj
        return obj


    def uut_update(self, key):
        box_id = BoxIndexStore.index_id(key)
        obj = self.uut_obj(box_id)

        obj.idc_name = 'idc'
        obj.room_name = 'room'
        obj.cabinet_name = 'cabinet'