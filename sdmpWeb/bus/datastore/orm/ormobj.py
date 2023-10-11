from pymongo import MongoClient
import datetime

class SqlDatabase:
    def __init__(self, model_class, using='default'):
        # 初始化 SqlDatabase 类
        self.model_class = model_class
        self.using = using

    def _get_queryset(self):
        # 获取查询集
        return self.model_class.objects.using(self.using)

    def sql_insert(self, **kwargs):
        # 插入数据
        return self._get_queryset().create(**kwargs)

    def sql_find(self, query):
        # 查询数据
        return self._get_queryset().filter(**query)

    def get_uid(self, uid):
        # 获取指定 uid 的数据，如果不存在则创建
        return self._get_queryset().get_or_create(uid=uid)[0]

    def sql_get(self, query):
        # 获取指定查询条件的数据，如果不存在则创建
        obj, _ = self._get_queryset().get_or_create(**query)
        return obj

    def _save_object(self, obj):
        # 保存对象
        obj.save(using=self.using)

    def sql_set(self, query, **kwargs):
        # 设置指定查询条件的属性值
        db = self.sql_get(query)
        for field, value in kwargs.items():
            setattr(db, field, value)
        self._save_object(db)

    def sql_update(self, query, **kwargs):
        # 更新指定查询条件的数据
        self.sql_update_one(query, **kwargs)

    def sql_update_one(self, query, **kwargs):
        # 更新符合查询条件的数据
        obj, _ = self._get_queryset().update_or_create(defaults=kwargs, **query)


class MongoDatabase:
    def __init__(self, clt=''):
        # 初始化 MongoDatabase 类，连接到 MongoDB
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

    def mongo_delete(self, query):
        # 删除单个文档
        result = self.collection.delete_one(query)
        return result.deleted_count

    def mongo_delete_many(self, query):
        # 删除多个文档
        result = self.collection.delete_many(query)
        return result.deleted_count

    def mongo_is_exit(self, query, value, ratio):
        query_value = dict(query)
        query_value.update({'value': value})
        document = self.mongo_find_one(query)
        if document is not None:
            item = self.mongo_find_one(query_value)
            if item is not None:
                return True
            else:
                if abs(document['value'] - value) < ratio:
                    return True
        return False


class OrmObj(SqlDatabase, MongoDatabase):
    def __init__(self, model_class, using='default'):
        # 初始化 OrmObj 类
        super().__init__(model_class, using)
        MongoDatabase.__init__(self, model_class._meta.db_table)
