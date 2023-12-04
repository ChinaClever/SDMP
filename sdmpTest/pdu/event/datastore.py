from pdu.index.datastore import PduIndexStore
from pdu.event.models import PduEventModel

class PduEventStore:

    def append(self, key, type, content):
        obj = PduEventModel()
        obj.event_type = type
        obj.event_content = content
        obj.pdu_id = PduIndexStore.get_id(key)
        obj.save()