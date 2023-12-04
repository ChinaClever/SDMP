from .datastore import RackDataStore, RackHdaStore
from rack.tests import rack_test_debug


def rack_test_hda():
    RackDataStore().updates()

    rack_test_debug()
    RackHdaStore().appends()
    rack_test_debug()

    # print(list(obj.index_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')

