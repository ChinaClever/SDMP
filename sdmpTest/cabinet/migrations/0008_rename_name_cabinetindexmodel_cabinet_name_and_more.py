# Generated by Django 4.2.7 on 2023-11-28 06:53

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('cabinet', '0007_cabinethdamodel_overhead'),
    ]

    operations = [
        migrations.RenameField(
            model_name='cabinetindexmodel',
            old_name='name',
            new_name='cabinet_name',
        ),
        migrations.RenameField(
            model_name='cabinetindexmodel',
            old_name='rid',
            new_name='room_id',
        ),
    ]
