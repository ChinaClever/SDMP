from django.apps import AppConfig


class CabinetConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'cabinet'


    def ready(self):
            # 启动后台任务的逻辑
            from cabinet.datastore.orm import manager
            manager.my_test_fun()
            # print("aaaaaaaaaaaaaa")