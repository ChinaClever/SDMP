from datetime import datetime
from django.db import transaction
from room.data.models import RoomDataModel
from room.index.datastore import RoomIndexStore
from cabinet.data.datastore import CabinetDataStore
from typing import Dict


class RoomDataStore:
    m_objects: Dict[int, RoomDataModel] = {}

    def __init__(self):
        RoomIndexStore()
        CabinetDataStore()
        if not RoomDataStore.m_objects:
             self._init()

    @staticmethod
    def _init():
        all_objects = RoomDataModel.objects.all()
        RoomDataStore.m_objects = {obj.room_id: obj for obj in all_objects}

    @staticmethod
    def get_objs():
        return RoomDataStore.m_objects.values()

    @classmethod
    def saves(cls):
        with transaction.atomic():
            for obj in cls.m_objects.values():
                if RoomIndexStore.is_exist(obj.room_id):
                    obj.updatetime = datetime.now()
                    obj.save()

    @classmethod
    def get_obj(cls, room_id: int) -> RoomDataModel:
        obj = cls.m_objects.get(room_id)
        if obj is None:
            obj = RoomDataModel(room_id=room_id)
            cls.m_objects[room_id] = obj
        return obj

    @staticmethod
    def _calculate_power_factor(obj):
        if obj.apparent_power > 0:
            obj.power_factor = min(obj.active_power / obj.apparent_power, 0.99)
        else:
            obj.power_factor = 0
        return obj

    @classmethod
    def room_update(cls, room_id):
        active_power, apparent_power, total_ele = CabinetDataStore.add_up(room_id)
        obj = cls.get_obj(room_id)
        obj.total_ele = total_ele
        obj.active_power = active_power
        obj.apparent_power = apparent_power
        cls._calculate_power_factor(obj)


    @classmethod
    def updates(cls):
        room_ids = RoomIndexStore.get_ids()
        for room_id in room_ids:
            cls.room_update(room_id)



