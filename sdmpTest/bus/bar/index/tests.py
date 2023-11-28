from .datastore import BarIndexStore
from bus.tests import bus_test_debug
import uuid

def bar_test_index_insert():
    obj = BarIndexStore()

    bus_test_debug()
    obj.index_init()

    bus_test_debug()
    for i in range(1, 2):
        obj.index_update(uuid.uuid4())

    bus_test_debug()
    obj.update_obj()
    bus_test_debug()
    obj.index_saves()

    obj.index_update('qq')
    print(obj.index_id('qq'))

    bus_test_debug()
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')
