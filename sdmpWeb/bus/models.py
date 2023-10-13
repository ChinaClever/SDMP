from django.db import models

# Create your models here.


class BarIndex(models.Model):
    class Meta: db_table = 'bus_bar_index'
    uid = models.CharField(max_length=128, unique=True, db_index=True)
    run_status = models.PositiveSmallIntegerField(default=0, verbose_name='运行状态') # 运行状态 选项：0=正常 1=预警 2=告警 3= 升级 4=故障 5=离线
    current_alarm = models.CharField(max_length=256, null=True, verbose_name='当前报警')
    dev_key = models.CharField(max_length=64, null=True)
    createtime = models.DateTimeField(auto_now_add=True)
    updatetime = models.DateTimeField(auto_now=True)

class BoxIndex(models.Model):
    class Meta: db_table = 'bus_box_index'
    bar = models.ForeignKey(to=BarIndex, on_delete=models.CASCADE, null=True) # blank=True
    uid = models.CharField(max_length=128, unique=True, db_index=True)
    run_status = models.PositiveSmallIntegerField(default=0, verbose_name='运行状态') # 运行状态 选项：0=正常 1=预警 2=告警 3= 升级 4=故障 5=离线
    current_alarm = models.CharField(max_length=256, null=True, verbose_name='当前报警')
    dev_key = models.CharField(max_length=64, null=True)
    createtime = models.DateTimeField(auto_now_add=True)
    updatetime = models.DateTimeField(auto_now=True)


class BarDev(models.Model):
    class Meta: db_table = 'bus_bar_dev'
    bar = models.OneToOneField(to=BarIndex, unique=True, on_delete=models.CASCADE)  # 一对多
    dev_addr = models.PositiveSmallIntegerField(default=0, verbose_name='设备地址')
    dev_spec = models.PositiveSmallIntegerField(default=0, verbose_name='电流规格')  # 0：标准  1：250A	1：400A  2：650A
    dev_mode = models.PositiveSmallIntegerField(default=0, verbose_name='设备模式')  # 0：有线 1：无线
    com_baud = models.PositiveSmallIntegerField(default=0, verbose_name='波特率')  # 1：9600  2：19200   3：38400   4：57600
    custom_made = models.PositiveSmallIntegerField(default=0, verbose_name='项目ID')  # 0：标准  1:定制
    alarm_filter = models.PositiveSmallIntegerField(default=0, verbose_name='告警滤波')  # 连续2-5次
    iof_module = models.PositiveSmallIntegerField(default=0, verbose_name='iOF触点')  # 0：没有  1：有
    buzzer = models.PositiveSmallIntegerField(default=0, verbose_name='蜂鸣器')  # 0：开启  1：关闭
    box_num = models.PositiveSmallIntegerField(default=0, verbose_name='插接箱数量')
    ac_dc = models.PositiveSmallIntegerField(default=0, verbose_name='交直流')  # 0 交流   1 直流
    hz = models.PositiveSmallIntegerField(default=0, verbose_name='频率')
    thunder_module = models.PositiveSmallIntegerField(default=0, verbose_name='防雷模块')  # 0：无  1：配有
    thunder_status = models.PositiveSmallIntegerField(default=0, verbose_name='防雷状态')  # 1：工作正常   2：损坏
    isd_module = models.PositiveSmallIntegerField(default=0, verbose_name='ISD报警触点')  # 0：无  1：配有
    release_module = models.PositiveSmallIntegerField(default=0, verbose_name='分离脱扣器模块')  # 0：无  1：配有
    aftercur_module = models.PositiveSmallIntegerField(default=0, verbose_name='剩余电流监测模块')  # 0：无  1：配有
    auto_addr_en = models.PositiveSmallIntegerField(default=0, verbose_name='自动设置地址开关')
    auto_addr_mode = models.PositiveSmallIntegerField(default=0, verbose_name='自动设置地址模式')
    auto_addr_status = models.PositiveSmallIntegerField(default=0, verbose_name='自动设置地址状态')
    ip_v4 = models.CharField(max_length=64, null=True, verbose_name='ip_v4')
    ip_v6 = models.CharField(max_length=64, null=True, verbose_name='ip_v6')
    sw_version = models.CharField(max_length=64, null=True, verbose_name='软件版本')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')

class BoxDev(models.Model):
    class Meta: db_table = 'bus_box_dev'
    box = models.OneToOneField(to=BoxIndex, unique=True, on_delete=models.CASCADE)  # 一对多
    line_num = models.PositiveSmallIntegerField(default=1, verbose_name='相数量')  # 相数量 1=单相，3=三相
    loop_num = models.PositiveSmallIntegerField(default=0, verbose_name='回路数量')  # 回路数量 1 - 6
    outlet_num = models.PositiveSmallIntegerField(default=0, verbose_name='插接位数量')
    dev_addr = models.PositiveSmallIntegerField(default=0, verbose_name='设备地址')
    dev_spec = models.PositiveSmallIntegerField(default=0, verbose_name='电流规格')  # 0：标准  1：250A	1：400A  2：650A
    dev_mode = models.PositiveSmallIntegerField(default=0, verbose_name='设备模式')  # 0：有线 1：无线
    com_baud = models.PositiveSmallIntegerField(default=0, verbose_name='波特率')  # 1：9600  2：19200   3：38400   4：57600
    custom_made = models.PositiveSmallIntegerField(default=0, verbose_name='项目ID')  # 0：标准  1:定制
    alarm_filter = models.PositiveSmallIntegerField(default=0, verbose_name='告警滤波')  # 连续2-5次
    iof_module = models.PositiveSmallIntegerField(default=0, verbose_name='iOF触点')  # 0：没有  1：有
    buzzer = models.PositiveSmallIntegerField(default=0, verbose_name='蜂鸣器')  # 0：开启  1：关闭
    sw_version = models.CharField(max_length=64, null=True, verbose_name='软件版本')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')


class BarData(models.Model):
    class Meta: db_table = 'bus_bar_data'
    bar = models.ForeignKey(to=BarIndex, on_delete=models.CASCADE)
    # 0:统计 1:相 2:回路 3:插接位 4:线 6:环境
    type = models.PositiveSmallIntegerField(default=0)

    # 1:断路器 2:电压 3:电流 4:有功功率 5:电能 6:功率因素 7:视在功率 8:无功功率
    # 9:谐波含量 10:负载百分比 11:温度 12:三相不平衡 21:剩余电流 22:零线电流
    topic = models.PositiveSmallIntegerField(default=0)
    indexes = models.PositiveSmallIntegerField(default=0)
    value = models.FloatField(default=0)
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')

class BarHda(models.Model):
    class Meta: db_table = 'bus_bar_hda'
    bar = models.ForeignKey(to=BarIndex, on_delete=models.CASCADE)
    # 0:统计 1:相 2:回路 3:插接位 4:线 6:环境
    type = models.PositiveSmallIntegerField(default=0)

    # 1:断路器 2:电压 3:电流 4:有功功率 5:电能 6:功率因素 7:视在功率 8:无功功率
    # 9:谐波含量 10:负载百分比 11:温度 12:三相不平衡 21:剩余电流 22:零线电流
    topic = models.PositiveSmallIntegerField(default=0)
    indexes = models.PositiveSmallIntegerField(default=0)
    value = models.FloatField(default=0)
    createtime = models.DateTimeField(auto_now_add=True)

class BarThreshold(models.Model):
    class Meta: db_table = 'bus_bar_threshold'
    bar = models.ForeignKey(to=BarIndex, on_delete=models.CASCADE)
    # 0:统计 1:相 2:回路 3:插接位 4:线 6:环境
    type = models.PositiveSmallIntegerField(default=0)

    # 1:断路器 2:电压 3:电流 4:有功功率 5:电能 6:功率因素 7:视在功率 8:无功功率
    # 9:谐波含量 10:负载百分比 11:温度 12:三相不平衡 21:剩余电流 22:零线电流
    topic = models.PositiveSmallIntegerField(default=0)
    # 1：当前值 2：额定值 3：报警状态 4：最大值 5：最小值 6：下临界值 7：上临界值 8：使能状态
    subtopic = models.PositiveSmallIntegerField(default=0)
    indexes = models.PositiveSmallIntegerField(default=0)
    value = models.FloatField(default=0)
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')

class BoxData(models.Model):
    class Meta: db_table = 'bus_box_data'
    box = models.ForeignKey(to=BoxIndex, on_delete=models.CASCADE)
    # 0:统计 1:相 2:回路 3:插接位 4:线 6:环境
    type = models.PositiveSmallIntegerField(default=0)

    # 1:断路器 2:电压 3:电流 4:有功功率 5:电能 6:功率因素 7:视在功率 8:无功功率
    # 9:谐波含量 10:负载百分比 11:温度 12:三相不平衡 21:剩余电流 22:零线电流
    topic = models.PositiveSmallIntegerField(default=0)
    indexes = models.PositiveSmallIntegerField(default=0)
    value = models.FloatField(default=0)
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')

class BoxHda(models.Model):
    class Meta: db_table = 'bus_box_hda'
    box = models.ForeignKey(to=BoxIndex, on_delete=models.CASCADE)
    # 0:统计 1:相 2:回路 3:插接位 4:线 6:环境
    type = models.PositiveSmallIntegerField(default=0)

    # 1:断路器 2:电压 3:电流 4:有功功率 5:电能 6:功率因素 7:视在功率 8:无功功率
    # 9:谐波含量 10:负载百分比 11:温度 12:三相不平衡 21:剩余电流 22:零线电流
    topic = models.PositiveSmallIntegerField(default=0)
    indexes = models.PositiveSmallIntegerField(default=0)
    value = models.FloatField(default=0)
    createtime = models.DateTimeField(auto_now_add=True)

class BoxThreshold(models.Model):
    class Meta: db_table = 'bus_box_threshold'
    box = models.ForeignKey(to=BoxIndex, on_delete=models.CASCADE)
    # 0:统计 1:相 2:回路 3:插接位 4:线 6:环境
    type = models.PositiveSmallIntegerField(default=0)

    # 1:断路器 2:电压 3:电流 4:有功功率 5:电能 6:功率因素 7:视在功率 8:无功功率
    # 9:谐波含量 10:负载百分比 11:温度 12:三相不平衡 21:剩余电流 22:零线电流
    topic = models.PositiveSmallIntegerField(default=0)
    # 1：当前值 2：额定值 3：报警状态 4：最大值 5：最小值 6：下临界值 7：上临界值 8：使能状态
    subtopic = models.PositiveSmallIntegerField(default=0)
    indexes = models.PositiveSmallIntegerField(default=0)
    value = models.FloatField(default=0)
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')



class BarAlarm(models.Model):
    class Meta: db_table = 'bus_bar_alarm'
    bar = models.ForeignKey(to=BarIndex, on_delete=models.CASCADE)  # 一对多
    alarm_status = models.CharField(max_length=64, blank=True, null=True, verbose_name='报警类型')
    alarm_content = models.CharField(max_length=128, blank=True, null=True, verbose_name='报警内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')

class BoxAlarm(models.Model):
    class Meta: db_table = 'bus_box_alarm'
    box = models.ForeignKey(to=BoxIndex, on_delete=models.CASCADE)  # 一对多
    alarm_status = models.CharField(max_length=64, blank=True, null=True, verbose_name='报警类型')
    alarm_content = models.CharField(max_length=128, blank=True, null=True, verbose_name='报警内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')




class BarEvent(models.Model):
    class Meta: db_table = 'bus_bar_event'
    bar = models.ForeignKey(to=BarIndex, on_delete=models.CASCADE)  # 一对多
    event_type = models.CharField(max_length=64, blank=True, null=True, verbose_name='事件类型')
    event_content = models.CharField(max_length=128, blank=True, null=True, verbose_name='事件内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')


class BoxEvent(models.Model):
    class Meta: db_table = 'bus_box_event'
    box = models.ForeignKey(to=BoxIndex, on_delete=models.CASCADE)  # 一对多
    event_type = models.CharField(max_length=64, blank=True, null=True, verbose_name='事件类型')
    event_content = models.CharField(max_length=128, blank=True, null=True, verbose_name='事件内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')



class BarUut(models.Model):
    class Meta: db_table = 'bus_bar_uut'
    bar = models.OneToOneField(to=BarIndex, unique=True, on_delete=models.CASCADE)  # 一对多
    dev_sn = models.CharField(max_length=64, null=True, verbose_name='序列号')
    dev_type = models.CharField(max_length=64, null=True, verbose_name='设备型号')
    room_name = models.CharField(max_length=64, null=True, verbose_name='机房名称')
    dev_position = models.CharField(max_length=64, null=True, verbose_name='设备位置')
    qrcode = models.CharField(max_length=256, null=True, verbose_name='二维码内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')

class BoxUut(models.Model):
    class Meta: db_table = 'bus_box_uut'
    box = models.OneToOneField(to=BoxIndex, unique=True, on_delete=models.CASCADE)  # 一对多
    dev_sn = models.CharField(max_length=64, null=True, verbose_name='序列号')
    dev_type = models.CharField(max_length=64, null=True, verbose_name='设备型号')
    room_name = models.CharField(max_length=64, null=True, verbose_name='机房名称')
    dev_position = models.CharField(max_length=64, null=True, verbose_name='设备位置')
    qrcode = models.CharField(max_length=256, null=True, verbose_name='二维码内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')