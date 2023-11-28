from bus.box.index.datastore import BoxIndexStore
from bus.box.event.models import BoxEventModel

class BoxEventStore:

    def append(self, key, type, content):
        obj = BoxEventModel()
        obj.event_type = type
        obj.event_content = content
        obj.box_id = BoxIndexStore.index_id(key)
        obj.save()
