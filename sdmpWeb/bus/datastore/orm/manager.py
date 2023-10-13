from .ormobj import OrmObj
from bus.models import *
from .enums import *

class Bar:
    _bar_dev_obj = OrmObj(BarDev)
    _bar_hda_obj = OrmObj(BarHda)
    _bar_uut_obj = OrmObj(BarUut)
    _bar_data_obj = OrmObj(BarData)
    _bar_index_obj = OrmObj(BarIndex)
    _bar_event_obj = OrmObj(BarEvent)
    _bar_alarm_obj = OrmObj(BarAlarm)
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
                res = 550
            elif type == EType.Loop:
                res = 300
            else:
                res = 150
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

    @classmethod
    def bar_alarm_append(cls, uid, alarm, msg, db=None):
        id = cls.bar_index_get(uid).id
        cls._bar_alarm_obj.sql_insert(bar_id=id, alarm_status=alarm, alarm_content=msg)
        if db is not None:
            cls._bar_alarm_obj.mongo_insert({'bar_id': id, 'alarm_status': alarm, 'alarm_content': msg})

    @classmethod
    def bar_event_append(cls, uid, type, msg, db=None):
        id = cls.bar_index_get(uid).id
        cls._bar_event_obj.sql_insert(bar_id=id, event_type=type, event_content=msg)
        if db is not None:
            cls._bar_event_obj.mongo_insert({'bar_id': id, 'event_type': type, 'event_content': msg})



class Box:
    _box_dev_obj = OrmObj(BoxDev)
    _box_hda_obj = OrmObj(BoxHda)
    _box_uut_obj = OrmObj(BoxUut)
    _box_data_obj = OrmObj(BoxData)
    _box_index_obj = OrmObj(BoxIndex)
    _box_event_obj = OrmObj(BoxEvent)
    _box_alarm_obj = OrmObj(BoxAlarm)
    _box_threshold_obj = OrmObj(BoxThreshold)
    _box_index_mUuidKeyDict = {}
    _box_index_id = 0
    _box_uid_str = ''

    @classmethod
    def box_index_get(cls, uid):
        index = cls._box_index_mUuidKeyDict.get(uid)
        if index is None:
            index = cls._box_index_obj.get_uid(uid)
            cls._box_index_mUuidKeyDict[uid] = index
            cls._box_index_obj.mongo_update({'id': index.id}, {'uid': uid})
        return index

    @classmethod
    def box_index_id(cls, uid):
        index = cls.box_index_get(uid)
        cls._box_index_id = index.id
        cls._box_uid_str = uid
        return index.id

    @classmethod
    def box_index_set(cls, key, value):
        index = cls.box_index_get(cls._box_uid_str)
        document = cls._box_index_obj.mongo_find_one({'id': index.id, key: value})
        if document is None:
            setattr(index, key, value)
            index.save(using=cls._box_index_obj.using)
            cls._box_index_obj.mongo_update({'id': index.id}, {key: value})


    @classmethod
    def _box_append_orm(cls, obj, type, topic, indexes, value, sub=None, db=None):
        document_map = {
            'box_id': cls._box_index_id,
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
    def box_hda_append(cls, type, topic, indexes, value):
        cls._box_append_orm(obj=cls._box_hda_obj, type=type, topic=topic, indexes=indexes,
                        value=value, sub=None, db=None)

    @classmethod
    def _box_ratio(cls, type, topic, sub, value):
        res = 0
        if sub is not None and sub != ESub.Value:
            return res
        elif topic == ETopic.Ele:
            if type == EType.Line:
                res = 50
            elif type == EType.Loop:
                res = 25
            else:
                res = 10
        elif topic == ETopic.Tem:
            res = 5
        elif topic == ETopic.Vol:
            res = 10
        else:
            res = value * 0.1
        return res

    @classmethod
    def _box_update_orm(cls, obj, type, topic, indexes, value, sub=None, db=None):
        query = {
            'box_id': cls._box_index_id,
            'type': type.value,
            'topic': topic.value,
            'indexes': indexes
        }
        if sub is not None:
            query['subtopic'] = sub.value
        res = obj.mongo_is_exit(query, value, 0)
        if db is not None or not res:
            obj.sql_update_one(query=query, value=value)
        ratio = cls._box_ratio(type, topic, sub, value)
        res = obj.mongo_is_exit(query, value, ratio)
        obj.mongo_update(query, {'value': value})
        # if db is not None or not res:
        #     obj.update_one(query=query, value=value)
        return res

    @classmethod
    def box_data_set(cls, type, topic, indexes, value):
        res = cls._box_update_orm(obj=cls._box_data_obj, type=type, topic=topic, indexes=indexes,
                              value=value, sub=None, db=None)
        if not res:
            cls.box_hda_append(type, topic, indexes, value)

    @classmethod
    def box_threshold_set(cls, type, topic, sub, indexes, value):
        res = cls._box_update_orm(obj=cls._box_threshold_obj, type=type, topic=topic, indexes=indexes,
                              value=value, sub=sub, db=None)

    @classmethod
    def _box_set(cls, obj, db=None, **kwargs):
        query = {'box_id': cls._box_index_id}
        query_kwoxgs = dict(query)
        query_kwoxgs.update(kwargs)
        document = obj.mongo_find_one(query_kwoxgs)
        if document is None or db is not None:
            obj.sql_update(query, **kwargs)
            obj.mongo_update(query, kwargs)

    @classmethod
    def box_dev_set(cls, db=None, **kwargs):
        cls._box_set(cls._box_dev_obj, db, **kwargs)

    @classmethod
    def box_uut_set(cls, db=None, **kwargs):
        cls._box_set(cls._box_uut_obj, db, **kwargs)

    @classmethod
    def box_alarm_append(cls, uid, alarm, msg, db=None):
        id = cls.box_index_get(uid).id
        cls._box_alarm_obj.sql_insert(box_id=id, alarm_status=alarm, alarm_content=msg)
        if db is not None:
            cls._box_alarm_obj.mongo_insert({'box_id': id, 'alarm_status': alarm, 'alarm_content': msg})

    @classmethod
    def box_event_append(cls, uid, type, msg, db=None):
        id = cls.box_index_get(uid).id
        cls._box_event_obj.sql_insert(box_id=id, event_type=type, event_content=msg)
        if db is not None:
            cls._box_event_obj.mongo_insert({'box_id': id, 'event_type': type, 'event_content': msg})



class Manager(Box):

    pass




def my_test_fun():
    uuid_str = "f47ac10b-58cc-4372-a567-0e02b2c3d479"
    id = Manager.box_index_id(uuid_str)
    Manager.box_index_set('current_alarm', 'lzy')
    Manager.box_index_set('bar_id', 1)
    Manager.box_hda_append(EType.Line, ETopic.Vol, 1, 256)
    Manager.box_data_set(EType.Line, ETopic.Vol, 1, 256)
    Manager.box_threshold_set(EType.Line, ETopic.Vol, ESub.VMax, 1,256)
    Manager.box_uut_set(dev_sn='aaaaaaaaaaa')
    Manager.box_alarm_append(uuid_str, 'alarm', 'abc', True)
    Manager.box_event_append(uuid_str, 'alarm', 'abc', True)



    # Manager.threshold_set(DType.Line, DTopic.Vol, DSub.Value,4,6)

    # Manager.dev_set(ip_v4="luo", ip_v6="45jjtruui46")


    