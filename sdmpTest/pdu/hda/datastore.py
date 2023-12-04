from pdu.index.datastore import PduIndexStore
from pdu.hda.models import PduHdaModel
from django.db import transaction

class PduHdaStore:
    def __init__(self):
        self.objects = []

    def saves(self):
        with transaction.atomic():
            for obj in self.objects:
                obj.save()
            self.objects.clear()

    def append(self, key, _type, topic, indexes, value):
        obj = PduHdaModel()
        obj.type = _type
        obj.topic = topic
        obj.indexes = indexes
        obj.value = value
        obj.pdu_id = PduIndexStore.get_id(key)
        self.objects.append(obj)



