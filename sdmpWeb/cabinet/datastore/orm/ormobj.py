from pymongo import MongoClient
import datetime


from cabinet.models import *


class SqlDatabase:
    def __init__(self, model_class, using='default'):
        self.model_class = model_class
        self.using = using

    def _get_queryset(self):
        # 获取查询集
        return self.model_class.objects.using(self.using)

    def values_list(self, fields):
        queryset = self._get_queryset()
        return list(queryset.values_list(fields, flat=True))

    def _filter_records(self, cabinet_id, field_name, **kwargs):
        queryset = self._get_queryset()
        if cabinet_id is not None:
            queryset = queryset.filter(cabinet=cabinet_id)
        return list(queryset.filter(**kwargs).values_list(field_name, flat=True))

    def sql_pdu_ids(self, cabinet_id):
        return self._filter_records(cabinet_id, 'pdu_id', pdu_id__gt=0)

    def sql_box_ids(self, cabinet_id):
        return self._filter_records(cabinet_id, 'box_id', box_id__gt=0)

    def sql_insert(self, **kwargs):
        # 插入数据
        return self._get_queryset().create(**kwargs)

    def sql_find(self, **kwargs):
        # 查询数据
        return self._get_queryset().filter(**kwargs).first()

    def sql_update(self, id, **kwargs):
        # 更新指定 cabinet_id 的数据
        self.sql_update_one({'cabinet_id': id}, **kwargs)

    def sql_update_one(self, query, **kwargs):
        # 更新符合条件的数据
        obj, _ = self._get_queryset().update_or_create(defaults=kwargs, **query)





class MongoDatabase:
    def __init__(self, clt=''):
        # 连接到 MongoDB
        self.client = MongoClient('localhost', 27017, connect=False, maxPoolSize=10)
        self.db = self.client['sdmp_data']
        # 如果集合不存在，则创建集合
        if clt not in self.db.list_collection_names():
            self.db.create_collection(clt)
        self.collection = self.db[clt]

    def mongo_insert(self, document):
        # 插入单个文档
        document['createtime'] = datetime.datetime.now()
        result = self.collection.insert_one(document)
        return result.inserted_id

    def mongo_insert_many(self, documents):
        # 插入多个文档
        result = self.collection.insert_many(documents)
        return result.inserted_ids

    def mongo_find(self, query):
        # 查询多个文档
        return self.collection.find(query)

    def mongo_find_one(self, query):
        # 查询单个文档
        return self.collection.find_one(query)

    def mongo_update(self, query, new_values):
        # 更新单个文档
        new_values['updatetime'] = datetime.datetime.now()
        document = self.mongo_find_one(query)
        if document:
            self.collection.update_one(query, {'$set': new_values})
        else:
            self.mongo_insert({**query, **new_values})

    def mongo_update_many(self, query, new_values):
        # 更新多个文档
        result = self.collection.update_many(query, new_values)
        return result.modified_count

    def mongo_is_exist(self, query, value, ratio):
        document = self.mongo_find_one(query)
        if document is not None:
            apparent_power = document.get('apparent_power', 0)
            if abs(apparent_power - value) <= ratio * apparent_power:
                return True
        return False



class OrmObj(SqlDatabase, MongoDatabase):
    def __init__(self, model_class, using='default'):
        super().__init__(model_class, using)
        MongoDatabase.__init__(self, model_class._meta.db_table)






