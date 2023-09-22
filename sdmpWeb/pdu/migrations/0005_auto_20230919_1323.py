# Generated by Django 3.2.12 on 2023-09-19 05:23

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('pdu', '0004_auto_20230919_1256'),
    ]

    operations = [
        migrations.CreateModel(
            name='PduHda',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('type', models.PositiveSmallIntegerField(default=0)),
                ('topic', models.PositiveSmallIntegerField(default=0)),
                ('indexes', models.PositiveSmallIntegerField(default=0)),
                ('value', models.FloatField(default=0)),
                ('createtime', models.DateTimeField(auto_now_add=True, verbose_name='创建时间')),
                ('pdu', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='pdu.pduindex')),
            ],
            options={
                'db_table': 'pdu_hda',
            },
        ),
        migrations.DeleteModel(
            name='PduEvent',
        ),
    ]
