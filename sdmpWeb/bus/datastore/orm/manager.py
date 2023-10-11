from .ormobj import OrmObj
from bus.models import *
from .enums import *

class Bar:
    _bar_dev_obj = OrmObj(BarDev)
    _bar_hda_obj = OrmObj(BarHda)
    _bar_uut_obj = OrmObj(BarUut)
    _bar_data_obj = OrmObj(BarData)
    _bar_index_obj = OrmObj(BarIndex)
    _bar_threshold_obj = OrmObj(BarThreshold)
    _bar_index_mUuidKeyDict = {}
    _bar_index_id = 0
    _bar_uid_str = ''

    @classmethod
    def bar_index_get(cls, uid):
        index = cls._bar_index_mUuidKeyDict.get(uid)
        if index is None:
            index = cls._bar_index_obj.get_uid(uid)
            cls._bar_index_mUuidKeyDict[uid] = index
            cls._bar_index_obj.mongo_update({'id': index.id}, {'uid': uid})
        return index

    @classmethod
    def bar_index_id(cls, uid):
        index = cls.bar_index_get(uid)
        cls._bar_index_id = index.id
        cls._bar_uid_str = uid
        return index.id

    @classmethod
    def bar_index_set(cls, key, value):
        index = cls.bar_index_get(cls._bar_uid_str)
        document = cls._bar_index_obj.mongo_find_one({'id': index.id, key: value})
        if document is None:
            setattr(index, key, value)
            index.save(using=cls._bar_index_obj.using)
            cls._bar_index_obj.mongo_update({'id': index.id}, {key: value})


    @classmethod
    def _bar_append_orm(cls, obj, type, topic, indexes, value, sub=None, db=None):
        document_map = {
            'bar_id': cls._bar_index_id,
            'type': type.value,
            'topic': topic.value,
            'indexes': indexes,
            'value': value
        }
        if sub is not None:
            document_map['subtopic'] = sub.value
        obj.sql_insert(**document_map)
        if db is not None:
            obj.mongo_insert(document_map)

    @classmethod
    def bar_hda_append(cls, type, topic, indexes, value):
        cls._bar_append_orm(obj=cls._bar_hda_obj, type=type, topic=topic, indexes=indexes,
                        value=value, sub=None, db=None)



    @classmethod
    def _bar_ratio(cls, type, topic, sub, value):
        res = 0
        if sub is not None and sub != ESub.Value:
            return res
        elif topic == ETopic.Ele:
            if type == EType.Line:
                res = 50
            elif type == EType.Loop:
                res = 30
            else:
                res = 15
        elif topic == ETopic.Tem:
            res = 5
        elif topic == ETopic.Vol:
            res = 10
        else:
            res = value * 0.1
        return res

    @classmethod
    def _bar_update_orm(cls, obj, type, topic, indexes, value, sub=None, db=None):
        query = {
            'bar_id': cls._bar_index_id,
            'type': type.value,
            'topic': topic.value,
            'indexes': indexes
        }
        if sub is not None:
            query['subtopic'] = sub.value
        res = obj.mongo_is_exit(query, value, 0)
        if db is not None or not res:
            obj.sql_update_one(query=query, value=value)
        ratio = cls._bar_ratio(type, topic, sub, value)
        res = obj.mongo_is_exit(query, value, ratio)
        obj.mongo_update(query, {'value': value})
        # if db is not None or not res:
        #     obj.update_one(query=query, value=value)
        return res


    @classmethod
    def bar_data_set(cls, type, topic, indexes, value):
        res = cls._bar_update_orm(obj=cls._bar_data_obj, type=type, topic=topic, indexes=indexes,
                              value=value, sub=None, db=None)
        if not res:
            cls.bar_hda_append(type, topic, indexes, value)

    @classmethod
    def bar_threshold_set(cls, type, topic, sub, indexes, value):
        res = cls._bar_update_orm(obj=cls._bar_threshold_obj, type=type, topic=topic, indexes=indexes,
                              value=value, sub=sub, db=None)

    @classmethod
    def _bar_set(cls, obj, db=None, **kwargs):
        query = {'bar_id': cls._bar_index_id}
        query_kwargs = dict(query)
        query_kwargs.update(kwargs)
        document = obj.mongo_find_one(query_kwargs)
        if document is None or db is not None:
            obj.sql_update(query, **kwargs)
            obj.mongo_update(query, kwargs)

    @classmethod
    def bar_dev_set(cls, db=None, **kwargs):
        cls._bar_set(cls._bar_dev_obj, db, **kwargs)

    @classmethod
    def bar_uut_set(cls, db=None, **kwargs):
        cls._bar_set(cls._bar_uut_obj, db, **kwargs)





class Manager(Bar):

    pass




def my_test_fun():
    uuid_str = "f47ac10b-58cc-4372-a567-0e02b2c3d479"
    id = Manager.bar_index_id(uuid_str)
    Manager.bar_index_set('current_alarm', 'lzy')
    Manager.bar_threshold_set(EType.Line, ETopic.Vol, ESub.VMax, 1,256)
    Manager.bar_uut_set(dev_sn='aaaaaaaaaaa')




    # Manager.threshold_set(DType.Line, DTopic.Vol, DSub.Value,4,6)

    # Manager.dev_set(ip_v4="luo", ip_v6="45jjtruui46")


    