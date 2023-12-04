from cabinet.index.datastore import CabinetIndexStore
from cabinet.temp_data.datastore import CabinetTempDataStore
from cabinet.temp_hda.models import CabinetTempHdaModel
from django.db import transaction

class CabinetTempHdaStore:

    @classmethod
    def _saves(cls, objects):
        with transaction.atomic():
            for obj in objects:
                if CabinetIndexStore.is_exist(obj.cabinet_id):
                    obj.save()

    @classmethod
    def appends(cls):
        hda_objects = []
        data_objects = CabinetTempDataStore.get_objs()
        for data_obj in data_objects:
            hda_obj = CabinetTempHdaModel(
                a_1=data_obj.a_1,
                a_2=data_obj.a_2,
                a_3=data_obj.a_3,
                a_4=data_obj.a_4,
                b_1=data_obj.b_1,
                b_2=data_obj.b_2,
                b_3=data_obj.b_3,
                b_4=data_obj.b_4,
            )
            hda_objects.append(hda_obj)
        cls._saves(hda_objects)