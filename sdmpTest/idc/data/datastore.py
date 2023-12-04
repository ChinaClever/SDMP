from datetime import datetime
from django.db import transaction
from idc.data.models import IdcDataModel
from idc.index.datastore import IdcIndexStore
from room.data.datastore import RoomDataStore
from typing import Dict


class IdcDataStore:
    m_objects: Dict[int, IdcDataModel] = {}

    def __init__(self):
        IdcIndexStore()
        RoomDataStore()
        if not IdcDataStore.m_objects:
             self._init()

    @staticmethod
    def _init():
        all_objects = IdcDataModel.objects.all()
        IdcDataStore.m_objects = {obj.idc_id: obj for obj in all_objects}

    @staticmethod
    def get_objs():
        return IdcDataStore.m_objects.values()

    @classmethod
    def saves(cls):
        with transaction.atomic():
            for obj in cls.m_objects.values():
                if IdcIndexStore.is_exist(obj.idc_id):
                    obj.updatetime = datetime.now()
                    obj.save()

    @classmethod
    def get_obj(cls, idc_id: int) -> IdcDataModel:
        obj = cls.m_objects.get(idc_id)
        if obj is None:
            obj = IdcDataModel(idc_id=idc_id)
            cls.m_objects[idc_id] = obj
        return obj

    @staticmethod
    def _calculate_power_factor(obj):
        if obj.apparent_power > 0:
            obj.power_factor = min(obj.active_power / obj.apparent_power, 0.99)
        else:
            obj.power_factor = 0
        return obj

    @classmethod
    def idc_update(cls, idc_id):
        active_power, apparent_power, total_ele = RoomDataStore.add_up(idc_id)
        obj = cls.get_obj(idc_id)
        obj.total_ele = total_ele
        obj.active_power = active_power
        obj.apparent_power = apparent_power
        cls._calculate_power_factor(obj)


    @classmethod
    def updates(cls):
        idc_ids = IdcIndexStore.get_ids()
        for idc_id in idc_ids:
            cls.idc_update(idc_id)

