from django.apps import AppConfig


class PduConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'pdu'

    def ready(self):
        from pdu.uut import tests
        # tests.test_thread()
        # print("aaaaaaaaaaaaaa")
