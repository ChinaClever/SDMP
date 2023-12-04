from bus.tests import bus_test_debug
from .datastore import BarUutStore
from bus.bar.index.datastore import BarIndexStore


def bar_test_uut_insert():
    pdu = BarUutStore()
    bus_test_debug('a')
    BarIndexStore.index_init()

    bus_test_debug('b')
    for i in range(1, 101):
        pdu.uut_update('qq')

    bus_test_debug()
    pdu.uut_saves()
    bus_test_debug()
    print('================================')
