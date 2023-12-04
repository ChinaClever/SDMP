from rack.index.models import RackIndexModel
from typing import Dict, List


class RackIndexStore:
    m_objects: Dict[int, RackIndexModel] = {}

    def __init__(self):
        if not RackIndexStore.m_objects:
            RackIndexStore.init()
    @classmethod
    def init(cls):
        cls.m_objects = {obj.id: obj for obj in RackIndexModel.objects.all()}

    @classmethod
    def get_ids(cls):
         return  cls.m_objects.keys()

    @classmethod
    def get_obj(cls, id):
        return cls.m_objects.get(id)

    @classmethod
    def is_exist(cls, id):
        return id in cls.m_objects

