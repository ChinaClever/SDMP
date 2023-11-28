from .datastore import BoxHdaStore
from bus.box.index.datastore import BoxIndexStore
from bus.tests import bus_test_debug



def box_test_hda_insert():
    obj = BoxHdaStore()
    bus_test_debug()
    BoxIndexStore.index_init()

    bus_test_debug()
    for i in range(1, 10001):
        obj.append('qq', 1,2,3, 4)

    bus_test_debug()
    obj.hda_saves()
    bus_test_debug()
    print('================================')
