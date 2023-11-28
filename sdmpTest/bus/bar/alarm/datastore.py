from bus.bar.index.datastore import BarIndexStore
from bus.bar.alarm.models import BarAlarmModel

class BarAlarmStore:

    def append(self, key, status, content):
        obj = BarAlarmModel()
        obj.alarm_status = status
        obj.alarm_content = content
        obj.bar_id = BarIndexStore.index_id(key)
        obj.save()

