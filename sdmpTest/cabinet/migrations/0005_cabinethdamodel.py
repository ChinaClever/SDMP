# Generated by Django 4.2.7 on 2023-11-24 05:22

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('cabinet', '0004_rename_ele_cabinetdatamodel_power_factor_and_more'),
    ]

    operations = [
        migrations.CreateModel(
            name='CabinetHdaModel',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('apparent_power', models.FloatField(default=0)),
                ('active_power', models.FloatField(default=0)),
                ('power_factor', models.FloatField(default=0)),
                ('total_ele', models.FloatField(default=0)),
                ('createtime', models.DateTimeField(auto_now_add=True)),
                ('cabinet', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='cabinet.cabinetindexmodel')),
            ],
            options={
                'db_table': 'cabinet_hda',
            },
        ),
    ]
