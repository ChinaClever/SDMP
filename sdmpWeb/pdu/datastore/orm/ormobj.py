
from pymongo import MongoClient
import datetime

class SqlObj:
    def __init__(self, model_class, using='default'):
        self.model_class = model_class
        self.using = using

    def _get_queryset(self):
        return self.model_class.objects.using(self.using)

    def insert(self, **kwargs):
        return self._get_queryset().create(**kwargs)

    def find(self, **kwargs):
        return self._get_queryset().filter(**kwargs)

    def get_uid(self, uid):
        return self._get_queryset().get_or_create(uid=uid)[0]

    def add(self, pdu_id):
        kwargs = {'pdu_id': pdu_id}
        return self._get_queryset().get_or_create(**kwargs)[0]

    def get(self, pdu_id):
        kwargs = {'pdu_id': pdu_id}
        obj, _ = self._get_queryset().get_or_create(**kwargs)
        return obj

    def _save_object(self, obj):
        obj.save(using=self.using)

    def set(self, pdu_id, key, value):
        db = self.get(pdu_id)
        setattr(db, key, value)
        self._save_object(db)

    def update(self, pdu_id, **kwargs):
        self.update_one({'pdu_id': pdu_id}, **kwargs)

    def update_one(self, query, **kwargs):
        obj, _ = self._get_queryset().update_or_create(**query, defaults=kwargs)


class MongoObj:
    def __init__(self, clt=''):
        # 连接到 MongoDB
        self.client = MongoClient('localhost', 27017, connect=False, maxPoolSize=10)
        self.db = self.client['sdmp_data']
        # 如果集合不存在，则创建集合
        if clt not in self.db.list_collection_names():
            self.db.create_collection(clt)
        self.collection = self.db[clt]

    def insert_document(self, document):
        # 插入单个文档
        document['createtime'] = datetime.datetime.now()
        result = self.collection.insert_one(document)
        return result.inserted_id

    def insert_documents(self, documents):
        # 插入多个文档
        result = self.collection.insert_many(documents)
        return result.inserted_ids

    def find_documents(self, query):
        # 查询多个文档
        return self.collection.find(query)

    def find_document(self, query):
        # 查询单个文档
        return self.collection.find_one(query)

    def update_document(self, query, new_values):
        # 更新单个文档
        new_values['updatetime'] = datetime.datetime.now()
        document = self.find_document(query)
        if document:
            result = self.collection.update_one(query, {'$set': new_values})
            return result.modified_count
        else:
            inserted_id = self.insert_document({**query, **new_values})
            return inserted_id

    def update_documents(self, query, new_values):
        # 更新多个文档
        result = self.collection.update_many(query, new_values)
        return result.modified_count

    def delete_document(self, query):
        # 删除单个文档
        result = self.collection.delete_one(query)
        return result.deleted_count

    def delete_documents(self, query):
        # 删除多个文档
        result = self.collection.delete_many(query)
        return result.deleted_count

class OrmObj(SqlObj, MongoObj):
    def __init__(self, model_class, using='default'):
        super().__init__(model_class, using)
        MongoObj.__init__(self, model_class._meta.db_table)



