from datetime import datetime
from django.db import transaction
from pdu.uut.models import PduUutModel
from pdu.index.datastore import PduIndexStore
from typing import Dict





class PduUutStore:
    def __init__(self):
        self.objects: Dict[int, PduUutModel] = {}
        self.objects = {obj.pdu_id: obj for obj in PduUutModel.objects.all()}

    def saves(self):
        with transaction.atomic():
            for obj in self.objects.values():
                    obj.save()

    def get_obj(self, pdu_id: int) -> PduUutModel:
        obj = self.objects.get(pdu_id)
        if obj is None:
            obj = PduUutModel(pdu_id=pdu_id)
            self.objects[pdu_id] = obj
        return obj


    def update(self, key):
        pdu_id = PduIndexStore.get_id(key)
        obj = self.get_obj(pdu_id)

        obj.idc_name = 'idc'
        obj.room_name = 'room'
        obj.cabinet_name = 'cabinet'


