# Generated by Django 4.2.7 on 2023-11-24 03:41

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('cabinet', '0002_cabinetpdumodel_cabinetboxmodel'),
    ]

    operations = [
        migrations.CreateModel(
            name='CabinetDataModel',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('apparent_power', models.FloatField(default=0)),
                ('active_power', models.FloatField(default=0)),
                ('overhead', models.FloatField(default=0)),
                ('pf', models.FloatField(default=0)),
                ('ele', models.FloatField(default=0)),
                ('updatetime', models.DateTimeField(auto_now=True)),
                ('cabinet', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='cabinet.cabinetindexmodel')),
            ],
            options={
                'db_table': 'cabinet_data',
            },
        ),
    ]