from .datastore import RackIndexStore
from rack.tests import rack_test_debug


def rack_test_index():
    obj = RackIndexStore()
    rack_test_debug(obj.get_ids())


    # print(list(obj.index_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')


