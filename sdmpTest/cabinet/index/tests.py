from .datastore import CabinetIndexStore
from cabinet.tests import cabinet_test_debug



def cabinet_test_index():
    cabinet_test_debug()
    obj = CabinetIndexStore()
    cabinet_test_debug()

    print(list(obj.get_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')
