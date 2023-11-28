from .datastore import BarEventStore
from bus.bar.index.datastore import BarIndexStore
from bus.tests import bus_test_debug


def bar_test_event_insert():
    obj = BarEventStore()
    bus_test_debug()
    BarIndexStore.index_init()

    bus_test_debug()
    for i in range(1, 101):
        obj.append('qq', 1,2)

    bus_test_debug()
    print('================================')
