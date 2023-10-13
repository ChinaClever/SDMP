# Generated by Django 3.2.12 on 2023-09-26 09:28

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='BarIndex',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('uid', models.CharField(db_index=True, max_length=128, unique=True)),
                ('run_status', models.PositiveSmallIntegerField(default=0, verbose_name='运行状态')),
                ('current_alarm', models.CharField(max_length=256, null=True, verbose_name='当前报警')),
                ('dev_key', models.CharField(max_length=64, null=True)),
                ('createtime', models.DateTimeField(auto_now_add=True)),
                ('updatetime', models.DateTimeField(auto_now=True)),
            ],
            options={
                'db_table': 'bus_bar_index',
            },
        ),
        migrations.CreateModel(
            name='BoxIndex',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('uid', models.CharField(db_index=True, max_length=128, unique=True)),
                ('run_status', models.PositiveSmallIntegerField(default=0, verbose_name='运行状态')),
                ('current_alarm', models.CharField(max_length=256, null=True, verbose_name='当前报警')),
                ('dev_key', models.CharField(max_length=64, null=True)),
                ('createtime', models.DateTimeField(auto_now_add=True)),
                ('updatetime', models.DateTimeField(auto_now=True)),
                ('bar', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.barindex')),
            ],
            options={
                'db_table': 'bus_box_index',
            },
        ),
        migrations.CreateModel(
            name='BoxUut',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('dev_sn', models.CharField(max_length=64, null=True, verbose_name='序列号')),
                ('dev_type', models.CharField(max_length=64, null=True, verbose_name='设备型号')),
                ('room_name', models.CharField(max_length=64, null=True, verbose_name='机房名称')),
                ('dev_position', models.CharField(max_length=64, null=True, verbose_name='设备位置')),
                ('qrcode', models.CharField(max_length=256, null=True, verbose_name='二维码内容')),
                ('createtime', models.DateTimeField(auto_now_add=True, verbose_name='创建时间')),
                ('updatetime', models.DateTimeField(auto_now=True, verbose_name='更新时间')),
                ('box', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='bus.boxindex')),
            ],
            options={
                'db_table': 'bus_box_uut',
            },
        ),
        migrations.CreateModel(
            name='BoxThreshold',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('type', models.PositiveSmallIntegerField(default=0)),
                ('topic', models.PositiveSmallIntegerField(default=0)),
                ('subtopic', models.PositiveSmallIntegerField(default=0)),
                ('indexes', models.PositiveSmallIntegerField(default=0)),
                ('value', models.FloatField(default=0)),
                ('updatetime', models.DateTimeField(auto_now=True, verbose_name='更新时间')),
                ('box', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.boxindex')),
            ],
            options={
                'db_table': 'bus_box_threshold',
            },
        ),
        migrations.CreateModel(
            name='BoxHda',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('type', models.PositiveSmallIntegerField(default=0)),
                ('topic', models.PositiveSmallIntegerField(default=0)),
                ('indexes', models.PositiveSmallIntegerField(default=0)),
                ('value', models.FloatField(default=0)),
                ('createtime', models.DateTimeField(auto_now_add=True)),
                ('box', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.boxindex')),
            ],
            options={
                'db_table': 'bus_box_hda',
            },
        ),
        migrations.CreateModel(
            name='BoxEvent',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('event_type', models.CharField(blank=True, max_length=64, null=True, verbose_name='事件类型')),
                ('event_content', models.CharField(blank=True, max_length=128, null=True, verbose_name='事件内容')),
                ('createtime', models.DateTimeField(auto_now_add=True, verbose_name='创建时间')),
                ('box', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.boxindex')),
            ],
            options={
                'db_table': 'bus_box_event',
            },
        ),
        migrations.CreateModel(
            name='BoxDev',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('line_num', models.PositiveSmallIntegerField(default=1, verbose_name='相数量')),
                ('loop_num', models.PositiveSmallIntegerField(default=0, verbose_name='回路数量')),
                ('outlet_num', models.PositiveSmallIntegerField(default=0, verbose_name='插接位数量')),
                ('dev_addr', models.PositiveSmallIntegerField(default=0, verbose_name='设备地址')),
                ('dev_spec', models.PositiveSmallIntegerField(default=0, verbose_name='电流规格')),
                ('dev_mode', models.PositiveSmallIntegerField(default=0, verbose_name='设备模式')),
                ('com_baud', models.PositiveSmallIntegerField(default=0, verbose_name='波特率')),
                ('custom_made', models.PositiveSmallIntegerField(default=0, verbose_name='项目ID')),
                ('alarm_filter', models.PositiveSmallIntegerField(default=0, verbose_name='告警滤波')),
                ('iof_module', models.PositiveSmallIntegerField(default=0, verbose_name='iOF触点')),
                ('buzzer', models.PositiveSmallIntegerField(default=0, verbose_name='蜂鸣器')),
                ('sw_version', models.CharField(max_length=64, null=True, verbose_name='软件版本')),
                ('createtime', models.DateTimeField(auto_now_add=True, verbose_name='创建时间')),
                ('updatetime', models.DateTimeField(auto_now=True, verbose_name='更新时间')),
                ('box', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='bus.boxindex')),
            ],
            options={
                'db_table': 'bus_box_dev',
            },
        ),
        migrations.CreateModel(
            name='BoxData',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('type', models.PositiveSmallIntegerField(default=0)),
                ('topic', models.PositiveSmallIntegerField(default=0)),
                ('indexes', models.PositiveSmallIntegerField(default=0)),
                ('value', models.FloatField(default=0)),
                ('updatetime', models.DateTimeField(auto_now=True, verbose_name='更新时间')),
                ('box', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.boxindex')),
            ],
            options={
                'db_table': 'bus_box_data',
            },
        ),
        migrations.CreateModel(
            name='BoxAlarm',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('alarm_status', models.CharField(blank=True, max_length=64, null=True, verbose_name='报警类型')),
                ('alarm_content', models.CharField(blank=True, max_length=128, null=True, verbose_name='报警内容')),
                ('createtime', models.DateTimeField(auto_now_add=True, verbose_name='创建时间')),
                ('box', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.boxindex')),
            ],
            options={
                'db_table': 'bus_box_alarm',
            },
        ),
        migrations.CreateModel(
            name='BarUut',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('dev_sn', models.CharField(max_length=64, null=True, verbose_name='序列号')),
                ('dev_type', models.CharField(max_length=64, null=True, verbose_name='设备型号')),
                ('room_name', models.CharField(max_length=64, null=True, verbose_name='机房名称')),
                ('dev_position', models.CharField(max_length=64, null=True, verbose_name='设备位置')),
                ('qrcode', models.CharField(max_length=256, null=True, verbose_name='二维码内容')),
                ('createtime', models.DateTimeField(auto_now_add=True, verbose_name='创建时间')),
                ('updatetime', models.DateTimeField(auto_now=True, verbose_name='更新时间')),
                ('bar', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='bus.barindex')),
            ],
            options={
                'db_table': 'bus_bar_uut',
            },
        ),
        migrations.CreateModel(
            name='BarThreshold',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('type', models.PositiveSmallIntegerField(default=0)),
                ('topic', models.PositiveSmallIntegerField(default=0)),
                ('indexes', models.PositiveSmallIntegerField(default=0)),
                ('value', models.FloatField(default=0)),
                ('subtopic', models.PositiveSmallIntegerField(default=0)),
                ('updatetime', models.DateTimeField(auto_now=True, verbose_name='更新时间')),
                ('bar', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.barindex')),
            ],
            options={
                'db_table': 'bus_bar_threshold',
            },
        ),
        migrations.CreateModel(
            name='BarHda',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('type', models.PositiveSmallIntegerField(default=0)),
                ('topic', models.PositiveSmallIntegerField(default=0)),
                ('indexes', models.PositiveSmallIntegerField(default=0)),
                ('value', models.FloatField(default=0)),
                ('createtime', models.DateTimeField(auto_now_add=True)),
                ('bar', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.barindex')),
            ],
            options={
                'db_table': 'bus_bar_hda',
            },
        ),
        migrations.CreateModel(
            name='BarEvent',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('event_type', models.CharField(blank=True, max_length=64, null=True, verbose_name='事件类型')),
                ('event_content', models.CharField(blank=True, max_length=128, null=True, verbose_name='事件内容')),
                ('createtime', models.DateTimeField(auto_now_add=True, verbose_name='创建时间')),
                ('bar', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.barindex')),
            ],
            options={
                'db_table': 'bus_bar_event',
            },
        ),
        migrations.CreateModel(
            name='BarDev',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('dev_addr', models.PositiveSmallIntegerField(default=0, verbose_name='设备地址')),
                ('dev_spec', models.PositiveSmallIntegerField(default=0, verbose_name='电流规格')),
                ('dev_mode', models.PositiveSmallIntegerField(default=0, verbose_name='设备模式')),
                ('com_baud', models.PositiveSmallIntegerField(default=0, verbose_name='波特率')),
                ('custom_made', models.PositiveSmallIntegerField(default=0, verbose_name='项目ID')),
                ('alarm_filter', models.PositiveSmallIntegerField(default=0, verbose_name='告警滤波')),
                ('iof_module', models.PositiveSmallIntegerField(default=0, verbose_name='iOF触点')),
                ('buzzer', models.PositiveSmallIntegerField(default=0, verbose_name='蜂鸣器')),
                ('box_num', models.PositiveSmallIntegerField(default=0, verbose_name='插接箱数量')),
                ('ac_dc', models.PositiveSmallIntegerField(default=0, verbose_name='交直流')),
                ('hz', models.PositiveSmallIntegerField(default=0, verbose_name='频率')),
                ('thunder_module', models.PositiveSmallIntegerField(default=0, verbose_name='防雷模块')),
                ('thunder_status', models.PositiveSmallIntegerField(default=0, verbose_name='防雷状态')),
                ('isd_module', models.PositiveSmallIntegerField(default=0, verbose_name='ISD报警触点')),
                ('release_module', models.PositiveSmallIntegerField(default=0, verbose_name='分离脱扣器模块')),
                ('aftercur_module', models.PositiveSmallIntegerField(default=0, verbose_name='剩余电流监测模块')),
                ('auto_addr_en', models.PositiveSmallIntegerField(default=0, verbose_name='自动设置地址开关')),
                ('auto_addr_mode', models.PositiveSmallIntegerField(default=0, verbose_name='自动设置地址模式')),
                ('auto_addr_status', models.PositiveSmallIntegerField(default=0, verbose_name='自动设置地址状态')),
                ('ip_v4', models.CharField(max_length=64, null=True, verbose_name='ip_v4')),
                ('ip_v6', models.CharField(max_length=64, null=True, verbose_name='ip_v6')),
                ('sw_version', models.CharField(max_length=64, null=True, verbose_name='软件版本')),
                ('createtime', models.DateTimeField(auto_now_add=True, verbose_name='创建时间')),
                ('updatetime', models.DateTimeField(auto_now=True, verbose_name='更新时间')),
                ('bar', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='bus.barindex')),
            ],
            options={
                'db_table': 'bus_bar_dev',
            },
        ),
        migrations.CreateModel(
            name='BarData',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('type', models.PositiveSmallIntegerField(default=0)),
                ('topic', models.PositiveSmallIntegerField(default=0)),
                ('indexes', models.PositiveSmallIntegerField(default=0)),
                ('value', models.FloatField(default=0)),
                ('updatetime', models.DateTimeField(auto_now=True, verbose_name='更新时间')),
                ('bar', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.barindex')),
            ],
            options={
                'db_table': 'bus_bar_data',
            },
        ),
        migrations.CreateModel(
            name='BarAlarm',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('alarm_status', models.CharField(blank=True, max_length=64, null=True, verbose_name='报警类型')),
                ('alarm_content', models.CharField(blank=True, max_length=128, null=True, verbose_name='报警内容')),
                ('createtime', models.DateTimeField(auto_now_add=True, verbose_name='创建时间')),
                ('bar', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.barindex')),
            ],
            options={
                'db_table': 'bus_bar_alarm',
            },
        ),
    ]