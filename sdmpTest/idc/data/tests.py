from .datastore import IdcDataStore
from idc.tests import idc_test_debug


def idc_test_data():
    obj = IdcDataStore()

    obj.updates()
    idc_test_debug()
    obj.saves()
    idc_test_debug()

    # print(list(obj.index_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')



