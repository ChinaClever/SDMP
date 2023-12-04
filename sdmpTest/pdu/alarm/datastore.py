from pdu.index.datastore import PduIndexStore
from pdu.alarm.models import PduAlarmModel

class PduAlarmStore:

    def append(self, key, status, content):
        obj = PduAlarmModel()
        obj.alarm_status = status
        obj.alarm_content = content
        obj.pdu_id = PduIndexStore.get_id(key)
        obj.save()




