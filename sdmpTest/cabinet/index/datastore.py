from datetime import datetime
from django.db import transaction
from cabinet.index.models import CabinetIndexModel
from typing import Dict, List


class CabinetIndexStore:
    m_objects: Dict[int, CabinetIndexModel] = {}

    def __init__(self):
        if not CabinetIndexStore.m_objects:
            CabinetIndexStore.init()
    @classmethod
    def init(cls):
        cls.m_objects = {obj.id: obj for obj in CabinetIndexModel.objects.all()}

    @classmethod
    def get_ids(cls):
         return  cls.m_objects.keys()

    @classmethod
    def get_obj(cls, id):
        return cls.m_objects.get(id)

    @classmethod
    def list_by_room(cls, room_id):
        return [obj.id for obj in cls.m_objects.values() if obj.room_id == room_id]


    @classmethod
    def is_pdu_box(cls, id):
        obj = cls.m_objects.get(id)
        if obj:
            return obj.pdu_box if obj.pdu_box is not None else 0
        return 0

    @classmethod
    def is_exist(cls, id):
        return id in cls.m_objects

    @classmethod
    def pow_capacity(cls, id):
        return cls.m_objects.get(id).pow_capacity
