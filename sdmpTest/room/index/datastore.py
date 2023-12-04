from datetime import datetime
from django.db import transaction
from room.index.models import RoomIndexModel
from typing import Dict, List


class RoomIndexStore:
    m_objects: Dict[int, RoomIndexModel] = {}

    def __init__(self):
        if not RoomIndexStore.m_objects:
            RoomIndexStore.init()
    @classmethod
    def init(cls):
        cls.m_objects = {obj.id: obj for obj in RoomIndexModel.objects.all()}

    @classmethod
    def get_ids(cls):
         return  cls.m_objects.keys()

    @classmethod
    def is_exist(cls, id):
        return id in cls.m_objects

    @classmethod
    def list_by_idc(cls, idc_id):
        return [obj.id for obj in cls.m_objects.values() if obj.idc_id == idc_id]