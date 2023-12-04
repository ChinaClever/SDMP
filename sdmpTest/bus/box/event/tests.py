from .datastore import BoxEventStore
from bus.box.index.datastore import BoxIndexStore
from bus.tests import bus_test_debug


def box_test_event_insert():
    obj = BoxEventStore()
    bus_test_debug()
    BoxIndexStore.index_init()

    bus_test_debug()
    for i in range(1, 101):
        obj.append('qq', 1,2)

    bus_test_debug()
    print('================================')
