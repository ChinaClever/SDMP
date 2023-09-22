from django.apps import AppConfig


class PduConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'pdu'



    def ready(self):
        # 检查是否已经执行过后台任务
        if not self.is_task_executed():
            # 启动后台任务的逻辑

            from pdu.datastore.orm import manager
            manager.my_test_fun()
            print("aaaaaaaaaaaaaa")
            # from your_app_name.tasks import background_task
            # background_task.delay(arg1, arg2)
            # 将已执行标志保存到数据库或缓存中
            self.mark_task_as_executed()

    def is_task_executed(self):
        # 检查后台任务是否已经执行过
        # 在这里可以根据需求使用数据库、缓存或其他标记来判断
        # 返回True表示任务已执行，返回False表示任务未执行
        # 示例中使用了一个假设的标记变量
        return getattr(self, '_task_executed', False)

    def mark_task_as_executed(self):
        # 将任务执行标志保存到数据库、缓存或其他标记
        # 这里使用一个假设的标记变量
        self._task_executed = True