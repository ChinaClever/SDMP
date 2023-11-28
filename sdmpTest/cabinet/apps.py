from django.apps import AppConfig


class CabinetConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'cabinet'

    def ready(self):

        from cabinet.hda import tests
        # tests.cabinet_test_hda()
        # print("aaaaaaaaaaaaaa")