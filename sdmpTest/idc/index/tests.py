from .datastore import IdcIndexStore
from idc.tests import idc_test_debug


def idc_test_index():
    obj = IdcIndexStore()
    idc_test_debug(obj.get_ids())


    # print(list(obj.index_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')


