
from rack.data.datastore import RackDataStore
from rack.hda.models import RackHdaModel
from django.db import transaction
from rack.tests import rack_test_debug


class RackHdaStore:

    @classmethod
    def _saves(cls, objects):
        # with transaction.atomic():
        RackHdaModel.objects.bulk_create(objects, ignore_conflicts=True)


    @classmethod
    def appends(cls):
        hda_objects = []

        for i in range(1, 10001):
            data_objects = RackDataStore.get_objs()
            for data_obj in data_objects:
                hda_obj = RackHdaModel(
                    rack_id=data_obj.rack_id,
                    active_power=data_obj.active_power,
                    apparent_power=data_obj.apparent_power,
                    power_factor=data_obj.power_factor,
                    total_ele=data_obj.total_ele
                )
                hda_objects.append(hda_obj)

        rack_test_debug()
        cls._saves(hda_objects)
        rack_test_debug()

