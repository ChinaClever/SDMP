

from cabinet.associate.models import CabinetPduModel, CabinetBoxModel
from typing import Dict, List

class CabinetAssociatePduStore:
    m_objects: Dict[int, CabinetPduModel] = {}

    @classmethod
    def __init__(cls):
        if not cls.m_objects:
            cls.init()

    @classmethod
    def init(cls):
        cls.m_objects = {obj.cabinet_id: obj for obj in CabinetPduModel.objects.all()}

    @classmethod
    def cabinet_ids(cls):
        return list(cls.m_objects.keys())

    @classmethod
    def is_exist(cls, id):
        return id in cls.m_objects

    @classmethod
    def pdu_obj(cls, id):
        return cls.m_objects.get(id)

    @classmethod
    def pdu_id(cls, id, a_b):
        obj = cls.pdu_obj(id)
        if 1 == a_b:
            return obj.a_pdu_id
        elif 2 == a_b:
            return obj.b_pdu_id

        return 0



class CabinetAssociateBoxStore:
    m_objects = {}

    @classmethod
    def __init__(cls):
        if not cls.m_objects:
            cls.cabinet_box_init()

    @classmethod
    def cabinet_box_init(cls):
        cls.m_objects = {obj.cabinet_id: obj for obj in CabinetBoxModel.objects.all()}

    @classmethod
    def cabinet_ids(cls):
        return list(cls.m_objects.keys())

    @classmethod
    def box_obj(cls, id):
        return cls.m_objects.get(id)

