from cabinet.index.datastore import CabinetIndexStore
from cabinet.data.datastore import CabinetDataStore
from cabinet.hda.models import CabinetHdaModel
from django.db import transaction

class CabinetHdaStore:

    @classmethod
    def _saves(cls, objects):
        with transaction.atomic():
            for obj in objects:
                if CabinetIndexStore.is_exist(obj.cabinet_id):
                    obj.save()

    @classmethod
    def appends(cls):
        hda_objects = []
        data_objects = CabinetDataStore.get_objs()
        for data_obj in data_objects:
            hda_obj = CabinetHdaModel(
                cabinet_id=data_obj.cabinet_id,
                active_power=data_obj.active_power,
                apparent_power=data_obj.apparent_power,
                power_factor=data_obj.power_factor,
                total_ele=data_obj.total_ele,
                overhead = data_obj.overhead
            )
            hda_objects.append(hda_obj)
        cls._saves(hda_objects)


