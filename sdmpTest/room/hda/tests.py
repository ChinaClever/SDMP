from .datastore import RoomDataStore, RoomHdaStore
from room.tests import room_test_debug


def room_test_hda():
    RoomDataStore().updates()

    room_test_debug()
    RoomHdaStore().appends()
    room_test_debug()

    # print(list(obj.index_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')

