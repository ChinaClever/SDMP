from bus.tests import bus_test_debug
from .datastore import BoxUutStore
from bus.box.index.datastore import BoxIndexStore


def box_test_uut_insert():
    pdu = BoxUutStore()
    bus_test_debug('a')
    BoxIndexStore.index_init()

    bus_test_debug('b')
    for i in range(1, 101):
        pdu.uut_update('qq')

    bus_test_debug()
    pdu.uut_saves()
    bus_test_debug()
    print('================================')
