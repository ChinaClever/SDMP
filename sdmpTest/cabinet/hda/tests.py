from .datastore import CabinetDataStore, CabinetHdaStore
from cabinet.tests import cabinet_test_debug


def cabinet_test_hda():
    cabinet_test_debug()
    obj = CabinetDataStore()

    cabinet_test_debug()
    obj.updates()
    cabinet_test_debug()

    CabinetHdaStore.appends()
    cabinet_test_debug()

    # print(list(obj.index_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')


