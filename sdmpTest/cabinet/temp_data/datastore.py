from cabinet.associate.datastore import CabinetAssociatePduStore
from cabinet.associate.datastore import CabinetAssociateBoxStore


from datetime import datetime
from django.db import transaction
from cabinet.temp_data.models import CabinetTempDataModel
from cabinet.index.datastore import CabinetIndexStore
from pdu.index.datastore import PduIndexStore
from typing import Dict



class CabinetTempDataStore:
    m_objects: Dict[int, CabinetTempDataModel] = {}

    @staticmethod
    def get_objs():
        return CabinetTempDataStore.m_objects.values()

    @classmethod
    def get_obj(cls, cabinet_id: int) -> CabinetTempDataModel:
        obj = cls.m_objects.get(cabinet_id)
        if obj is None:
            obj = CabinetTempDataModel(cabinet_id=cabinet_id)
            cls.m_objects[cabinet_id] = obj
        return obj


    @classmethod
    def _calculate_combined_values(cls, cabinet_id, a_obj, b_obj):
        obj = cls.get_obj(cabinet_id)

        if a_obj.key:
             obj.a_1 = 1.1
             obj.a_2 = 1.2


        if b_obj.key:
            obj.b_1 = 2.1
            obj.b_2 = 2.2



    @classmethod
    def _update_data(cls, cabinet_id):
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
                cls._update_data(cabinet_id)







