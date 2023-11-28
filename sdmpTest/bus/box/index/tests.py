from .datastore import BoxIndexStore
from bus.tests import bus_test_debug
import uuid

from bus.bar.index.models import BarIndexModel
from bus.box.index.models import BoxIndexModel
from bus.box.hda.models import BoxHdaModel



def box_test_index_insert():
    obj = BoxIndexStore()

    bus_test_debug()
    obj.index_init()

    bus_test_debug()
    for i in range(1, 10001):
        obj.index_update(uuid.uuid4())

    bus_test_debug()
    obj.update_obj()
    bus_test_debug()
    obj.index_saves()

    obj.index_update('qq')
    print(obj.index_id('qq'))

    bus_test_debug()
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')