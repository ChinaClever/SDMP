from django.db import models

# Create your dbsql here.

class Index(models.Model):
    class Meta: db_table = 'pdu_index'
    id = models.AutoField(primary_key=True)
    uid = models.CharField(max_length=128, unique=True, db_index=True)
    run_status = models.PositiveSmallIntegerField(default=0, verbose_name='运行状态') # 运行状态 选项：0=正常 1=预警 2=告警 3= 升级 4=故障 5=离线
    current_alarm = models.CharField(max_length=256, null=True, verbose_name='当前报警')
    dev_key = models.CharField(max_length=64, null=True)
    createtime = models.DateTimeField(auto_now_add=True)
    updatetime = models.DateTimeField(auto_now=True)


class Dev(models.Model):
    class Meta:db_table = 'pdu_dev'
    id = models.AutoField(primary_key=True)
    pdu = models.OneToOneField(to=Index, unique=True, on_delete=models.CASCADE) # 一对一
    dev_type = models.CharField(max_length=64, null=True, verbose_name='设备型号')
    dev_spec = models.PositiveSmallIntegerField(default=0, verbose_name='设备规格') # 设备规格 1=A系列，2=B系列，3=C系列，4=D系列，
    dev_mode = models.PositiveSmallIntegerField(default=0, verbose_name='设备模式') # 设备模式 0：标准 1：级联 2：机架
    line_num = models.PositiveSmallIntegerField(default=1, verbose_name='相数量') # 相数量 1=单相，3=三相
    loop_num = models.PositiveSmallIntegerField(default=0, verbose_name='回路数量') # 回路数量 1 - 6
    output_num = models.PositiveSmallIntegerField(default=0, verbose_name='输出位数量')
    cascade_addr = models.PositiveSmallIntegerField(default=0, verbose_name='级联地址')
    sw_version = models.CharField(max_length=64, null=True, verbose_name='软件版本')
    ip_v4 = models.CharField(max_length=64, null=True, verbose_name='ip_v4')
    ip_v6 = models.CharField(max_length=64, null=True, verbose_name='ip_v6')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')

class Data(models.Model):
    """PDU实时数据表"""
    class Meta: db_table = 'pdu_data'
    pdu = models.ForeignKey(to=Index, on_delete=models.CASCADE)  # 一对多

    # 1=相数据 2=回路数据 3=输出位数据 4=分组数据 5=机架数据 6=环境（温湿度）
    # 7=传感器（门禁其他传感器）  0=统计数据（总功率，总电能）
    type = models.PositiveSmallIntegerField(default=0)

    # 1：开关 2：电压 3：电流 4：功率 5：电能 6：功率因数 7：视在功率 8：无功功率 9：电能记录
    # 10、线电压 11：温度 12：湿度 21：门禁1 22：门禁2 23：水禁 24：烟雾
    topic = models.PositiveSmallIntegerField(default=0)
    indexes = models.PositiveSmallIntegerField(default=0)
    value = models.FloatField(default=0)
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')


class Threshold(models.Model):
    """PDU实时数据表"""
    class Meta: db_table = 'pdu_threshold'
    pdu = models.ForeignKey(to=Index, on_delete=models.CASCADE)  # 一对多

    # 1=相数据 2=回路数据 3=输出位数据 4=分组数据 5=机架数据 6=环境（温湿度）
    # 7=传感器（门禁其他传感器）  0=统计数据（总功率，总电能）
    type = models.PositiveSmallIntegerField(default=0)

    # 1：开关 2：电压 3：电流 4：功率 5：电能 6：功率因数 7：视在功率 8：无功功率 9：电能记录
    # 10、线电压 11：温度 12：湿度 21：门禁1 22：门禁2 23：水禁 24：烟雾
    topic = models.PositiveSmallIntegerField(default=0)

    # 1：当前值（开关状态） 2：额定值 （断开告警） 3：报警状态 4：最大值（上电延时） 5：最小值（复位延时）
    # 6：下临界值（超限断电） 7：上临界值（定时开关） 8：使能状态（开关关键设备保护） 9：最大峰值（开关当前次数）
    subtopic = models.PositiveSmallIntegerField(default=0)
    indexes = models.PositiveSmallIntegerField(default=0)
    value = models.FloatField(default=0)
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')


class Hda(models.Model):
    """PDU事件记录表"""
    class Meta: db_table = 'pdu_hda'
    pdu = models.ForeignKey(to=Index, on_delete=models.CASCADE)  # 一对多

    # 1=相数据 2=回路数据 3=输出位数据 4=分组数据 5=机架数据 6=环境（温湿度）
    # 7=传感器（门禁其他传感器）  0=统计数据（总功率，总电能）
    type = models.PositiveSmallIntegerField(default=0)

    # 1：开关 2：电压 3：电流 4：功率 5：电能 6：功率因数 7：视在功率 8：无功功率 9：电能记录
    # 10、线电压 11：温度 12：湿度 21：门禁1 22：门禁2 23：水禁 24：烟雾
    topic = models.PositiveSmallIntegerField(default=0)
    indexes = models.PositiveSmallIntegerField(default=0)
    value = models.FloatField(default=0)
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')




class Alarm(models.Model): # PDU报警记录表
    class Meta: db_table = 'pdu_alarm'
    pdu = models.ForeignKey(to=Index, on_delete=models.CASCADE)  # 一对多
    alarm_status = models.CharField(max_length=64, blank=True, null=True, verbose_name='报警类型')
    alarm_content = models.CharField(max_length=128, blank=True, null=True, verbose_name='报警内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')

class Event(models.Model):
    """PDU事件记录表"""
    class Meta: db_table = 'pdu_event'
    pdu = models.ForeignKey(to=Index, on_delete=models.CASCADE)  # 一对多
    event_type = models.CharField(max_length=64, blank=True, null=True, verbose_name='事件类型')
    event_content = models.CharField(max_length=128, blank=True, null=True, verbose_name='事件内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')


class Uut(models.Model):
    class Meta: db_table = 'pdu_uut'
    id = models.AutoField(primary_key=True)
    pdu = models.OneToOneField(to=Index, unique=True, on_delete=models.CASCADE) # 一对一
    dev_sn = models.CharField(max_length=64, null=True, verbose_name='序列号')
    dev_type = models.CharField(max_length=64, null=True, verbose_name='设备型号')
    room_name = models.CharField(max_length=64, null=True, verbose_name='机房名称')
    dev_position = models.CharField(max_length=64, null=True, verbose_name='设备位置')
    qrcode = models.CharField(max_length=256, null=True, verbose_name='二维码内容')
    createtime = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')
    updatetime = models.DateTimeField(auto_now=True, verbose_name='更新时间')




