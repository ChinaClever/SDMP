from bus.box.index.datastore import BoxIndexStore
from bus.box.hda.models import BoxHdaModel
from django.db import transaction

class BoxHdaStore:
    def __init__(self):
        self.objects = []

    def hda_saves(self):
        with transaction.atomic():
            for obj in self.objects:
                obj.save()
            self.objects.clear()

    def append(self, key, _type, topic, indexes, value):
        obj = BoxHdaModel()
        obj.type = _type
        obj.topic = topic
        obj.indexes = indexes
        obj.value = value
        obj.box_id = BoxIndexStore.index_id(key)
        self.objects.append(obj)

