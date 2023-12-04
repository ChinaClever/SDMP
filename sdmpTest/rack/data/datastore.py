from datetime import datetime
from django.db import transaction
from rack.data.models import RackDataModel
from rack.index.datastore import RackIndexStore
from pdu.index.datastore import PduIndexStore
from cabinet.associate.datastore import CabinetAssociatePduStore

from typing import Dict


class RackDataStore:
    m_objects: Dict[int, RackDataModel] = {}


    def __init__(self):
        RackIndexStore()
        CabinetAssociatePduStore()
        if not RackDataStore.m_objects:
             self._init()

    @staticmethod
    def _init():
        all_objects = RackDataModel.objects.all()
        RackDataStore.m_objects = {obj.rack_id: obj for obj in all_objects}

    @staticmethod
    def get_objs():
        return RackDataStore.m_objects.values()

    @classmethod
    def saves(cls):
        with transaction.atomic():
            for obj in cls.m_objects.values():
                obj.updatetime = datetime.now()
                obj.save()

    @classmethod
    def get_obj(cls, rack_id: int) -> RackDataModel:
        obj = cls.m_objects.get(rack_id)
        if obj is None:
            obj = RackDataModel(rack_id=rack_id)
            cls.m_objects[rack_id] = obj
        return obj

    @staticmethod
    def _calculate_power_factor(obj):
        if obj.apparent_power > 0:
            obj.power_factor = min(obj.active_power / obj.apparent_power, 0.99)
        else:
            obj.power_factor = 0
        return obj



    @classmethod
    def rack_update(cls, rack_id):
        # a_pdu_id = CabinetAssociatePduStore.pdu_id(rack_id, 1)
        # b_pdu_id = CabinetAssociatePduStore.pdu_id(rack_id, 2)
        # a_pdu_key = PduIndexStore.get_key_by_id(a_pdu_id)


        # active_power, apparent_power, total_ele = CabinetDataStore.add_up(rack_id)
        obj = cls.get_obj(rack_id)
        obj.total_ele = 5
        obj.active_power = 6
        obj.apparent_power = 7
        cls._calculate_power_factor(obj)

    @classmethod
    def update_objs(cls):
        rack_ids = RackIndexStore.get_ids()
        keys_to_delete = []
        for key in cls.m_objects:
            if key not in rack_ids:
                keys_to_delete.append(key)
        for key in keys_to_delete:
            del cls.m_objects[key]
        return rack_ids

    @classmethod
    def updates(cls):
        rack_ids = cls.update_objs()
        for rack_id in rack_ids:
            cls.rack_update(rack_id)