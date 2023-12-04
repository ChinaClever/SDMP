from bus.bar.index.datastore import BarIndexStore
from bus.bar.event.models import BarEventModel

class BarEventStore:

    def append(self, key, type, content):
        obj = BarEventModel()
        obj.event_type = type
        obj.event_content = content
        obj.bar_id = BarIndexStore.index_id(key)
        obj.save()

