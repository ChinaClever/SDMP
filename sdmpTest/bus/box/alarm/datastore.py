from bus.box.index.datastore import BoxIndexStore
from bus.box.alarm.models import BoxAlarmModel

class BoxAlarmStore:

    def append(self, key, status, content):
        obj = BoxAlarmModel()
        obj.alarm_status = status
        obj.alarm_content = content
        obj.box_id = BoxIndexStore.index_id(key)
        obj.save()

