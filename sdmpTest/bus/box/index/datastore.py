from datetime import datetime
from django.db import transaction

from bus.box.index.models import BoxIndexModel
from typing import Dict

class BoxIndexStore:
    m_objects: Dict[str, BoxIndexModel] = {}
    modification_counts: Dict[str, int] = {}

    def __init__(self):
        if not BoxIndexStore.m_objects:
            BoxIndexStore.index_init()

    @classmethod
    def index_init(cls):
        cls.m_objects = {obj.key: obj for obj in BoxIndexModel.objects.all()}
        cls.modification_counts = {obj.key: 0 for obj in cls.m_objects.values()}

    def index_saves(self):
        with transaction.atomic():
            for obj in BoxIndexStore.m_objects.values():
                if self.modification_counts[obj.key] > 1:
                    self.modification_counts[obj.key] -= 1
                    obj.updatetime = datetime.now()
                    obj.save()
                elif obj.run_status != 5:
                    obj.run_status = 5
                    obj.save()


    @classmethod
    def index_obj(cls, key: str) -> BoxIndexModel:
        obj = cls.m_objects.get(key)
        if obj is None:
            obj = BoxIndexModel(key=key)
            cls.m_objects[key] = obj
        return obj

    @classmethod
    def index_id(cls, key: str) -> int:
        obj = cls.index_obj(key)
        if obj.id is None:
            obj.save()
        return obj.id

    @staticmethod
    def calculate_power_factor(obj):
        if obj.apparent_power > 0:
            obj.power_factor = min(obj.active_power / obj.apparent_power, 0.99)
        else:
            obj.power_factor = 0
        return obj


    def update_obj(self):
        for obj in BoxIndexStore.m_objects.values():
            obj.run_status = 0
            # obj.bar_id = 1
            obj.active_power = 0.9
            obj.apparent_power = 1.1
            obj.total_ele = 3.3
            self.modification_counts[obj.key] = 1


    def index_update(self, key):
        obj = self.index_obj(key)
        self.modification_counts[obj.key] = 1

        obj.bar_id = 1
        obj.run_status = 0
        obj.active_power = 0.9
        obj.apparent_power = 1.1
        obj.total_ele = 3.3

        return self.calculate_power_factor(obj)
