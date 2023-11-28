from datetime import datetime
from django.db import transaction
from pdu.index.models import PduIndexModel
from typing import Dict

class PduIndexStore:
    m_id_objects: Dict[int, PduIndexModel] = {}
    m_objects: Dict[str, PduIndexModel] = {}
    modification_counts: Dict[str, int] = {}

    def __init__(self):
        if not PduIndexStore.m_objects:
            PduIndexStore.init()

    @classmethod
    def init(cls):
        all_objects = PduIndexModel.objects.all()
        cls.m_objects = {obj.key: obj for obj in all_objects}
        cls.m_id_objects = {obj.id: obj for obj in all_objects}
        cls.modification_counts = {obj.key: 0 for obj in all_objects}

    def saves(self):
        with transaction.atomic():
            for obj in PduIndexStore.m_objects.values():
                if self.modification_counts[obj.key] > 1:
                    self.modification_counts[obj.key] -= 1
                    obj.updatetime = datetime.now()
                    obj.save()
                elif obj.run_status != 5:
                    obj.run_status = 5
                    obj.save()


    @classmethod
    def get_obj(cls, key: str) -> PduIndexModel:
        obj = cls.m_objects.get(key)
        if obj is None:
            obj = PduIndexModel(key=key)
            cls.m_objects[key] = obj
        return obj

    @classmethod
    def get_id(cls, key: str) -> int:
        obj = cls.get_obj(key)
        if obj.id is None:
            obj.save()
            cls.m_id_objects[obj.id] = obj
        return obj.id

    @classmethod
    def get_obj_by_id(cls, id: int) -> PduIndexModel:
        return cls.m_id_objects.get(id)




    @staticmethod
    def _calculate_power_factor(obj):
        if obj.apparent_power > 0:
            obj.power_factor = min(obj.active_power / obj.apparent_power, 0.99)
        else:
            obj.power_factor = 0
        return obj


    def update_objs(self):
        for obj in PduIndexStore.m_objects.values():
            obj.run_status = 0
            obj.active_power = 0.9
            obj.apparent_power = 1.1
            obj.total_ele = 3.3
            self.modification_counts[obj.key] = 1


    def update_obj(self, key):
        obj = self.get_obj(key)
        self.modification_counts[obj.key] = 1

        obj.run_status = 0
        obj.active_power = 0.9
        obj.apparent_power = 1.1
        obj.total_ele = 3.3

        return self._calculate_power_factor(obj)








