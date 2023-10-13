from django.apps import AppConfig


class BusConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'bus'

    def ready(self):
            # 启动后台任务的逻辑
            from bus.datastore.orm import manager
            # manager.my_test_fun()
            # print("aaaaaaaaaaaaaa")