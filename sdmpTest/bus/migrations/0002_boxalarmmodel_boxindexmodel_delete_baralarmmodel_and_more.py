# Generated by Django 4.2.7 on 2023-11-14 03:14

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('bus', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='BoxAlarmModel',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('alarm_status', models.CharField(blank=True, max_length=64, null=True, verbose_name='报警类型')),
                ('alarm_content', models.CharField(blank=True, max_length=128, null=True, verbose_name='报警内容')),
                ('createtime', models.DateTimeField(auto_now_add=True, verbose_name='创建时间')),
            ],
            options={
                'db_table': 'bus_box_alarm',
            },
        ),
        migrations.CreateModel(
            name='BoxIndexModel',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('key', models.CharField(db_index=True, max_length=128, unique=True)),
                ('run_status', models.PositiveSmallIntegerField(default=0, verbose_name='运行状态')),
                ('current_alarm', models.CharField(max_length=256, null=True, verbose_name='当前报警')),
                ('createtime', models.DateTimeField(auto_now_add=True)),
                ('updatetime', models.DateTimeField(auto_now=True)),
                ('apparent_power', models.FloatField(default=0)),
                ('active_power', models.FloatField(default=0)),
                ('power_factor', models.FloatField(default=0)),
                ('total_ele', models.FloatField(default=0)),
                ('dev_addr', models.PositiveSmallIntegerField(default=2, verbose_name='设备地址')),
                ('outlet_num', models.PositiveSmallIntegerField(default=3, verbose_name='插接位数量')),
                ('bar', models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='bus.barindexmodel')),
            ],
            options={
                'db_table': 'bus_box_index',
            },
        ),
        migrations.DeleteModel(
            name='BarAlarmModel',
        ),
        migrations.AddField(
            model_name='boxalarmmodel',
            name='box',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='bus.boxindexmodel'),
        ),
    ]
