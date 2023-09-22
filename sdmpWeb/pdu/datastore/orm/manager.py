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
    _uid_str = ''
    _index_id = 0

    @classmethod
    def index_get(cls, uid):
        pdu_index = cls._index_mUuidKeyDict.get(uid)
        if pdu_index is None:
            pdu_index = cls._index_obj.get_uid(uid)
            cls._index_mUuidKeyDict[uid] = pdu_index
            cls._index_obj.update_document({'id': pdu_index.id}, {'uid': uid})
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
        setattr(pdu_index, key, value) # pdu_index.dev_key = key
        pdu_index.save(using=cls._index_obj.using)
        cls._index_obj.update_document({'id': pdu_index.id}, {key: value})

    @classmethod
    def _update_orm(cls, obj, type, topic, indexes, value, sub=None, db=None):
        query = {'pdu_id': cls._index_id, 'type': type.value, 'topic': topic.value, 'indexes': indexes}
        if sub is not None:
            query['subtopic'] = sub.value
        if db is not None:
            obj.update_one(query=query, value=value)
        obj.update_document(query, {'value': value})


    @classmethod
    def _append_orm(cls, obj, type, topic, indexes, value, sub=None, db=None):
        map = {'pdu_id': cls._index_id, 'type': type.value, 'topic': topic.value, 'indexes': indexes, 'value':value}
        if sub is not None:
            map['subtopic'] = sub.value
        if db is not None:
            obj.insert_document(map)
        obj.insert(**map)

    @classmethod
    def data_set(cls, type, topic, indexes, value):
        cls._update_orm(obj=cls._data_obj, type=type, topic=topic, indexes=indexes,
                        value=value, sub=None, db=None)

    @classmethod
    def hda_append(cls, type, topic, indexes, value):
        cls._append_orm(obj=cls._hda_obj, type=type, topic=topic, indexes=indexes,
                        value=value, sub=None, db=None)

    @classmethod
    def threshold_set(cls, type, topic, sub, indexes, value):
        cls._update_orm(obj=cls._threshold_obj, type=type, topic=topic, indexes=indexes,
                        value=value, sub=sub, db=None)

    @classmethod
    def dev_set(cls, db=None, **kwargs):
        if db is not None: cls._dev_obj.update(cls._index_id, **kwargs)
        cls._dev_obj.update_document({'pdu_id': cls._index_id}, {**kwargs})

    @classmethod
    def uut_set(cls, db=None, **kwargs):
        if db is not None: cls._uut_obj.update(cls._index_id, **kwargs)
        cls._uut_obj.update_document({'pdu_id': cls._index_id}, {**kwargs})

    @classmethod
    def alarm_append(cls, uid, alarm, msg, db=None):
        pdu_id = cls.index_get(uid).id
        cls._alarm_obj.insert(pdu_id=pdu_id, alarm_status=alarm, alarm_content=msg)
        if db is not None:
            cls._event_obj.insert_document({'pdu_id': pdu_id, 'alarm_status':alarm, 'alarm_content':msg})

    @classmethod
    def event_append(cls, uid, type, msg, db=None):
        pdu_id = cls.index_get(uid).id
        cls._event_obj.insert(pdu_id=pdu_id, event_type=type, event_content=msg)
        if db is not None:
            cls._event_obj.insert_document({'pdu_id': pdu_id, 'event_type':type, 'event_content':msg})


from .enums import *

def my_test_fun():
    uuid_str = "f47ac10b-58cc-4372-a567-0e02b2c3d479"
    pdu_id = Manager.index_id(uuid_str)
    Manager.threshold_set(DType.Line, DTopic.Vol, DSub.Value,4,5)

    Manager.dev_set(ip_v4="luo", ip_v6="45jjtruui46")

    # Manager.index_set_value(uuid_str, "lzydddd")
    # Manager.uut_set_value(room_name="luo", dev_sn="4546")
    # Manager.alarm_append(uuid_str, "alarm", "msg")



    # PduThresholdManager().set_value(pdu_id, 1,2,3,4, 6)