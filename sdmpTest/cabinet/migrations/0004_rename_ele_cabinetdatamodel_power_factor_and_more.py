# Generated by Django 4.2.7 on 2023-11-24 05:13

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('cabinet', '0003_cabinetdatamodel'),
    ]

    operations = [
        migrations.RenameField(
            model_name='cabinetdatamodel',
            old_name='ele',
            new_name='power_factor',
        ),
        migrations.RenameField(
            model_name='cabinetdatamodel',
            old_name='pf',
            new_name='total_ele',
        ),
    ]
