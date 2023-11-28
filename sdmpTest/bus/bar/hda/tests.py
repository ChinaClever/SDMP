from .datastore import BarHdaStore
from bus.bar.index.datastore import BarIndexStore
from bus.tests import bus_test_debug



def bar_test_hda_insert():
    obj = BarHdaStore()
    bus_test_debug()
    BarIndexStore.index_init()

    bus_test_debug()
    for i in range(1, 10001):
        obj.append('qq', 1,2,3, 4)

    bus_test_debug()
    obj.saves()
    bus_test_debug()
    print('================================')
