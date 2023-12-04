from datetime import datetime
from django.db import transaction
from idc.index.models import IdcIndexModel
from typing import Dict, List


class IdcIndexStore:
    m_objects: Dict[int, IdcIndexModel] = {}

    def __init__(self):
        if not IdcIndexStore.m_objects:
            IdcIndexStore.init()
    @classmethod
    def init(cls):
        cls.m_objects = {obj.id: obj for obj in IdcIndexModel.objects.all()}

    @classmethod
    def get_ids(cls):
         return  cls.m_objects.keys()

    @classmethod
    def is_exist(cls, id):
        return id in cls.m_objects