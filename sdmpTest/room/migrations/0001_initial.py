# Generated by Django 4.2.7 on 2023-11-28 06:53

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='RoomIndexModel',
            fields=[
                ('id', models.AutoField(primary_key=True, serialize=False)),
                ('rid', models.IntegerField(db_index=True, default=0)),
                ('room_name', models.CharField(max_length=256, verbose_name='机房名称')),
                ('cabinet_num', models.PositiveSmallIntegerField(default=0, verbose_name='机柜数量')),
                ('location', models.CharField(max_length=64, null=True, verbose_name='位置')),
                ('createtime', models.DateTimeField(auto_now_add=True)),
                ('updatetime', models.DateTimeField(auto_now=True)),
            ],
            options={
                'db_table': 'room_index',
            },
        ),
    ]
