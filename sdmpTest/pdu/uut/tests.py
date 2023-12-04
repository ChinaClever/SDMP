from pdu.tests import pdu_test_debug
from .datastore import PduUutStore
from pdu.index.datastore import PduIndexStore


def test_pdu_uut_insert():
    pdu = PduUutStore()
    pdu_test_debug('a')
    PduIndexStore.init()

    pdu_test_debug('b')
    for i in range(1, 101):
        pdu.update('qq')

    pdu_test_debug()
    pdu.saves()
    pdu_test_debug()
    print('================================')



