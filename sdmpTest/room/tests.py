from django.test import TestCase

# Create your tests here.


import datetime
import inspect
import threading

# Create your tests here.


def room_test_debug(*args):
    current_time = datetime.datetime.now()
    time_with_ms = current_time.strftime("%H:%M:%S.%f")[:-3]

    # 获取上级调用栈信息
    frame = inspect.currentframe().f_back
    caller_method = inspect.getframeinfo(frame).function
    caller_line = frame.f_lineno

    msg = " ".join(map(str, args))
    print(time_with_ms + f" Method: {caller_method}, Line: {caller_line} " + msg)


def room_test_thread(fun):
    # 创建守护线程对象
    daemon_thread = threading.Thread(target=fun, daemon=True)

    # 启动守护线程
    daemon_thread.start()