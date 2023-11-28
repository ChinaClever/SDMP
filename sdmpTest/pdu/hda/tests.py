from .datastore import PduHdaStore
from pdu.index.datastore import PduIndexStore
from pdu.tests import pdu_test_debug



def test_pdu_hda_insert():
    pdu = PduHdaStore()
    pdu_test_debug()
    PduIndexStore.init()

    pdu_test_debug()
    for i in range(1, 10001):
        pdu.append('qq', 1,2,3, 4)

    pdu_test_debug()
    pdu.saves()
    pdu_test_debug()
    print('================================')






