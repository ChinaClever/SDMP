from idc.data.datastore import IdcDataStore
from idc.hda.models import IdcHdaModel
from django.db import transaction
from idc.tests import idc_test_debug


class IdcHdaStore:

    @classmethod
    def _saves(cls, objects):
        with transaction.atomic():
            IdcHdaModel.objects.bulk_create(objects, ignore_conflicts=True)


    @classmethod
    def appends(cls):
        hda_objects = []
        data_objects = IdcDataStore.get_objs()
        for data_obj in data_objects:
            hda_obj = IdcHdaModel(
                idc_id=data_obj.idc_id,
                active_power=data_obj.active_power,
                apparent_power=data_obj.apparent_power,
                power_factor=data_obj.power_factor,
                total_ele=data_obj.total_ele
            )
            hda_objects.append(hda_obj)
        cls._saves(hda_objects)


