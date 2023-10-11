from .ormobj import OrmObj
from pdu.models import *

class Manager:
    _dev_obj = OrmObj(Dev)
    _uut_obj = OrmObj(Uut)
    _hda_obj = OrmObj(Hda)
    _data_obj = OrmObj(Data)
    _event_obj = OrmObj(Event)
    _index_obj = OrmObj(Index)
    _alarm_obj = OrmObj(Alarm)
    _threshold_obj = OrmObj(Threshold)
    _index_mUuidKeyDict = {}
    _index_id = 0
    _uid_str = ''

    @classmethod
    def index_get(cls, uid):
        pdu_index = cls._index_mUuidKeyDict.get(uid)
        if pdu_index is None:
            pdu_index = cls._index_obj.get_uid(uid)
            cls._index_mUuidKeyDict[uid] = pdu_index
            cls._index_obj.mongo_update({'id': pdu_index.id}, {'uid': uid})
        return pdu_index

    @classmethod
    def index_id(cls, uid):
        pdu_index = cls.index_get(uid)
        cls._index_id = pdu_index.id
        cls._uid_str = uid
        return pdu_index.id

    @classmethod
    def index_set(cls, key, value):
        pdu_index = cls.index_get(cls._uid_str)
        document = cls._index_obj.mongo_find_one({'id': pdu_index.id, key: value})
        if document is None:
            setattr(pdu_index, key, value)
            pdu_index.save(using=cls._index_obj.using)
            cls._index_obj.mongo_update({'id': pdu_index.id}, {key: value})

    @classmethod
    def calculate_change_ratio(cls, value1, value2):
        if value1 == 0 and value2 == 0:
            return 0.0
        elif value1 == 0 or value2 == 0:
            return 100
        else:
            return abs(value2 - value1) / abs(value1)

    @classmethod
    def _pdu_ratio(cls, type, topic, sub, value):
        res = 0
        if sub is not None and sub != DSub.Value:
            return res
        if type == DType.Sensor:
            res = 0
        elif topic == DTopic.Ele:
            if type == DType.Line:
                res = 11
            elif type == DType.Loop:
                res = 6
            else:
                res = 1
        elif topic == DTopic.Tem:
            res = 5
        elif topic == DTopic.Hum:
            res = 10
        elif topic == DTopic.Vol:
            res = 10
        else:
            res = value * 0.1
        return res

    @classmethod
    def _update_orm(cls, obj, type, topic, indexes, value, sub=None, db=None):
        query = {
            'pdu_id': cls._index_id,
            'type': type.value,
            'topic': topic.value,
            'indexes': indexes
        }
        if sub is not None:
            query['subtopic'] = sub.value
        res = obj.mongo_is_exit(query, value, 0)
        if db is not None or not res:
            obj.sql_update_one(query=query, value=value)

        ratio = cls._pdu_ratio(type, topic, sub, value)
        res = obj.mongo_is_exit(query, value, ratio)
        obj.mongo_update(query, {'value': value})
        # if db is not None or not res:
        #     obj.update_one(query=query, value=value)
        return res

    @classmethod
    def _append_orm(cls, obj, type, topic, indexes, value, sub=None, db=None):
        document_map = {
            'pdu_id': cls._index_id,
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
    def data_set(cls, type, topic, indexes, value):
        res = cls._update_orm(obj=cls._data_obj, type=type, topic=topic, indexes=indexes,
                              value=value, sub=None, db=None)
        if not res:
            cls.hda_append(type, topic, indexes, value)

    @classmethod
    def hda_append(cls, type, topic, indexes, value):
        cls._append_orm(obj=cls._hda_obj, type=type, topic=topic, indexes=indexes,
                        value=value, sub=None, db=None)

    @classmethod
    def threshold_set(cls, type, topic, sub, indexes, value):
        res = cls._update_orm(obj=cls._threshold_obj, type=type, topic=topic, indexes=indexes,
                              value=value, sub=sub, db=None)

    @classmethod
    def dev_set(cls, db=None, **kwargs):
        document = cls._dev_obj.mongo_find_one({'pdu_id': cls._index_id, **kwargs})
        if document is None or db is not None:
            cls._dev_obj.sql_update(cls._index_id, **kwargs)
            cls._dev_obj.mongo_update({'pdu_id': cls._index_id}, {**kwargs})

    @classmethod
    def uut_set(cls, db=None, **kwargs):
        document = cls._uut_obj.mongo_find_one({'pdu_id': cls._index_id, **kwargs})
        if document is None or db is not None:
            cls._uut_obj.sql_update(cls._index_id, **kwargs)
            cls._uut_obj.mongo_update({'pdu_id': cls._index_id}, {**kwargs})


    @classmethod
    def alarm_append(cls, uid, alarm, msg, db=None):
        pdu_id = cls.index_get(uid).id
        cls._alarm_obj.sql_insert(pdu_id=pdu_id, alarm_status=alarm, alarm_content=msg)
        if db is not None:
            cls._event_obj.mongo_insert({'pdu_id': pdu_id, 'alarm_status': alarm, 'alarm_content': msg})

    @classmethod
    def event_append(cls, uid, type, msg, db=None):
        pdu_id = cls.index_get(uid).id
        cls._event_obj.sql_insert(pdu_id=pdu_id, event_type=type, event_content=msg)
        if db is not None:
            cls._event_obj.mongo_insert({'pdu_id': pdu_id, 'event_type': type, 'event_content': msg})






from .enums import *

def my_test_fun():
    uuid_str = "f47ac10b-58cc-4372-a567-0e02b2c3d479"
    pdu_id = Manager.index_id(uuid_str)
    Manager.threshold_set(DType.Line, DTopic.Vol, DSub.Value,4,6)

    Manager.dev_set(ip_v4="luo", ip_v6="45jjtruui46")

    # Manager.index_set_value(uuid_str, "lzydddd")
    # Manager.uut_set_value(room_name="luo", dev_sn="4546")
    # Manager.alarm_append(uuid_str, "alarm", "msg")



    # PduThresholdManager().set_value(pdu_id, 1,2,3,4, 6)