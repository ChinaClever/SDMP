from .datastore import RoomDataStore
from room.tests import room_test_debug


def room_test_data():
    obj = RoomDataStore()

    obj.updates()
    room_test_debug()
    obj.saves()
    room_test_debug()

    # print(list(obj.index_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')

