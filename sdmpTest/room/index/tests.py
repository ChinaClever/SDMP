from .datastore import RoomIndexStore
from room.tests import room_test_debug


def room_test_index():
    obj = RoomIndexStore()
    room_test_debug(obj.get_ids())


    # print(list(obj.index_ids()))
    print('aaaaaaaaaaaaaaaaaaaaaaaaa')

