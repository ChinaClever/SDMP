from .datastore import IdcDataStore, IdcHdaStore
from idc.tests import idc_test_debug


def idc_test_hda():
    IdcDataStore().updates()

    idc_test_debug()
    IdcHdaStore().appends()
    idc_test_debug()

    # print(list(obj.index_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')

