from bus.bar.index.datastore import BarIndexStore
from bus.bar.hda.models import BarHdaModel
from django.db import transaction

class BarHdaStore:
    def __init__(self):
        self.objects = []

    def saves(self):
        with transaction.atomic():
            for obj in self.objects:
                obj.save()
            self.objects.clear()

    def append(self, key, _type, topic, indexes, value):
        obj = BarHdaModel()
        obj.type = _type
        obj.topic = topic
        obj.indexes = indexes
        obj.value = value
        obj.bar_id = BarIndexStore.index_id(key)
        self.objects.append(obj)

