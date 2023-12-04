from django.apps import AppConfig


class BusConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'bus'

    def ready(self):
        # from bus.bar.index import tests
        # tests.bar_test_index_insert()

        from bus.bar.index import tests
        # tests.bar_test_index_insert()
        # print("aaaaaaaaaaaaaa")
