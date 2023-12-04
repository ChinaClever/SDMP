from .datastore import CabinetDataStore
from cabinet.tests import cabinet_test_debug



def cabinet_test_data():
    cabinet_test_debug()
    obj = CabinetDataStore()

    cabinet_test_debug()
    obj.updates()
    cabinet_test_debug()
    # obj.data_saves()
    cabinet_test_debug()
    
    # print(list(obj.index_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')

