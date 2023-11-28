from .datastore import PduIndexStore
from pdu.tests import pdu_test_debug
import uuid



def pdu_test_index_insert():
    pdu = PduIndexStore()

    pdu_test_debug()
    pdu.init()

    pdu_test_debug()
    for i in range(1, 10001):
        pdu.update_obj(uuid.uuid4())

    pdu_test_debug()
    pdu.update_objs()
    pdu_test_debug()
    pdu.saves()


    pdu.update_obj('qq')
    print(pdu.get_id('qq'))

    pdu_test_debug()
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')


