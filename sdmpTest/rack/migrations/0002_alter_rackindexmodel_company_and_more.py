# Generated by Django 4.2.7 on 2023-11-30 02:52

from decimal import Decimal
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('rack', '0001_initial'),
    ]

    operations = [
        migrations.AlterField(
            model_name='rackindexmodel',
            name='company',
            field=models.CharField(max_length=128, verbose_name='所属公司'),
        ),
        migrations.AlterField(
            model_name='rackindexmodel',
            name='rack_name',
            field=models.CharField(max_length=128, verbose_name='机架名称'),
        ),
        migrations.AlterField(
            model_name='rackindexmodel',
            name='remarks',
            field=models.CharField(max_length=256, null=True, verbose_name='备注'),
        ),
        migrations.CreateModel(
            name='RackHdaModel',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('apparent_power', models.DecimalField(decimal_places=3, default=Decimal('0.000'), max_digits=10)),
                ('active_power', models.DecimalField(decimal_places=3, default=Decimal('0.000'), max_digits=10)),
                ('power_factor', models.DecimalField(decimal_places=2, default=Decimal('0.00'), max_digits=4)),
                ('total_ele', models.DecimalField(decimal_places=1, default=Decimal('0.0'), max_digits=10)),
                ('createtime', models.DateTimeField(auto_now_add=True)),
                ('cabinet', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='rack.rackindexmodel')),
            ],
            options={
                'db_table': 'rack_hda',
            },
        ),
        migrations.CreateModel(
            name='RackDataModel',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('apparent_power', models.DecimalField(decimal_places=3, default=Decimal('0.000'), max_digits=10)),
                ('active_power', models.DecimalField(decimal_places=3, default=Decimal('0.000'), max_digits=10)),
                ('power_factor', models.DecimalField(decimal_places=2, default=Decimal('0.00'), max_digits=4)),
                ('total_ele', models.DecimalField(decimal_places=1, default=Decimal('0.0'), max_digits=10)),
                ('updatetime', models.DateTimeField(auto_now=True)),
                ('rack', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='rack.rackindexmodel')),
            ],
            options={
                'db_table': 'rack_data',
            },
        ),
    ]