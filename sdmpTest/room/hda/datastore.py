from room.index.datastore import RoomIndexStore
from room.data.datastore import RoomDataStore
from room.hda.models import RoomHdaModel
from django.db import transaction
from room.tests import room_test_debug


class RoomHdaStore:

    @classmethod
    def _saves(cls, objects):
        with transaction.atomic():
            RoomHdaModel.objects.bulk_create(objects, ignore_conflicts=True)


    @classmethod
    def appends(cls):
        hda_objects = []
        data_objects = RoomDataStore.get_objs()
        for data_obj in data_objects:
            hda_obj = RoomHdaModel(
                room_id=data_obj.room_id,
                active_power=data_obj.active_power,
                apparent_power=data_obj.apparent_power,
                power_factor=data_obj.power_factor,
                total_ele=data_obj.total_ele
            )
            hda_objects.append(hda_obj)
        cls._saves(hda_objects)
