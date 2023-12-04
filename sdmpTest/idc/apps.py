from django.apps import AppConfig


class IdcConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'idc'

    def ready(self):
        from idc.hda import tests
        # tests.idc_test_hda()
        # print("aaaaaaaaaaaaaa")