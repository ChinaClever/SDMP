from .datastore import BarAlarmStore
from bus.bar.index.datastore import BarIndexStore
from bus.tests import bus_test_debug

from bus.bar.index.models import BarIndexModel


def bar_test_alarm_insert():
    obj = BarAlarmStore()
    bus_test_debug()
    BarIndexStore.index_init()

    bus_test_debug()
    for i in range(1, 101):
        obj.append('qq', 1,2)

    bus_test_debug()
    print('================================')

