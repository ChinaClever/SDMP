
from cabinet.associate.datastore import CabinetAssociatePduStore
from cabinet.associate.datastore import CabinetAssociateBoxStore


from datetime import datetime
from django.db import transaction
from cabinet.data.models import CabinetDataModel
from cabinet.index.datastore import CabinetIndexStore
from pdu.index.datastore import PduIndexStore
from typing import Dict



class CabinetDataStore:
    m_objects: Dict[int, CabinetDataModel] = {}

    def __init__(self):
        CabinetAssociatePduStore()
        CabinetIndexStore()
        PduIndexStore()
        if not CabinetDataStore.m_objects:
             self._init()

    @staticmethod
    def _init():
        all_objects = CabinetDataModel.objects.all()
        CabinetDataStore.m_objects = {obj.cabinet_id: obj for obj in all_objects}

    @staticmethod
    def get_objs():
        return CabinetDataStore.m_objects.values()

    @classmethod
    def list_objs(cls, room_id):
        return [cls.get_obj(id) for id in CabinetIndexStore.list_by_room(room_id)]

    @classmethod
    def add_up(cls, room_id):
        objs = cls.list_objs(room_id)
        total_ele = sum(obj.total_ele for obj in objs)
        active_power = sum(obj.active_power for obj in objs)
        apparent_power = sum(obj.apparent_power for obj in objs)
        return active_power, apparent_power, total_ele


    @classmethod
    def saves(cls):
        with transaction.atomic():
            for obj in cls.m_objects.values():
                if CabinetIndexStore.is_exist(obj.cabinet_id):
                    obj.updatetime = datetime.now()
                    obj.save()

    @classmethod
    def get_obj(cls, cabinet_id: int) -> CabinetDataModel:
        obj = cls.m_objects.get(cabinet_id)
        if obj is None:
            obj = CabinetDataModel(cabinet_id=cabinet_id)
            cls.m_objects[cabinet_id] = obj
        return obj

    @staticmethod
    def _calculate_power_factor(obj):
        if obj.apparent_power > 0:
            obj.power_factor = min(obj.active_power / obj.apparent_power, 0.99)
        else:
            obj.power_factor = 0
        return obj

    @classmethod
    def _calculate_combined_values(cls, cabinet_id, a_obj, b_obj):
        active_power = 0
        apparent_power = 0
        total_ele = 0

        if a_obj.active_power:
            active_power += a_obj.active_power
            apparent_power += a_obj.apparent_power
            total_ele += a_obj.total_ele

        if b_obj.active_power:
            active_power += b_obj.active_power
            apparent_power += b_obj.apparent_power
            total_ele += b_obj.total_ele

        obj = cls.get_obj(cabinet_id)
        obj.active_power = active_power
        obj.apparent_power = apparent_power
        obj.total_ele = total_ele

        obj.overhead = CabinetIndexStore.pow_capacity(cabinet_id) - obj.apparent_power
        cls._calculate_power_factor(obj)

    @classmethod
    def _update_pdu(cls, cabinet_id):
        if CabinetAssociatePduStore.is_exist(cabinet_id):
            pdu = CabinetAssociatePduStore.pdu_obj(cabinet_id)
            a_pdu = PduIndexStore.get_obj_by_id(pdu.a_pdu_id)
            b_pdu = PduIndexStore.get_obj_by_id(pdu.b_pdu_id)
            cls._calculate_combined_values(cabinet_id, a_pdu, b_pdu)

    @classmethod
    def updates(cls):
        cabinet_ids = CabinetIndexStore.get_ids()
        for cabinet_id in cabinet_ids:
            pdu_box = CabinetIndexStore.is_pdu_box(cabinet_id)
            if pdu_box == 1:
                cls._update_pdu(cabinet_id)



