from .datastore import PduAlarmStore
from pdu.index.datastore import PduIndexStore
from pdu.tests import pdu_test_debug



def test_pdu_alarm_insert():
    pdu = PduAlarmStore()
    pdu_test_debug()
    PduIndexStore.init()

    pdu_test_debug()
    for i in range(1, 101):
        pdu.append('qq', 1,2)

    pdu_test_debug()
    print('================================')


