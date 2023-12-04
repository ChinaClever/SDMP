from django.apps import AppConfig


class RackConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'rack'

    def ready(self):
        from rack.hda import tests
        # tests.rack_test_hda()
        # print("aaaaaaaaaaaaaa")

