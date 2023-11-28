from .datastore import CabinetAssociatePduStore
from cabinet.tests import cabinet_test_debug



def cabinet_test_associate():
    cabinet_test_debug()
    obj = CabinetAssociatePduStore()
    cabinet_test_debug()

    print(list(obj.cabinet_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')