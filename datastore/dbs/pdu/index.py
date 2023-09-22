from dbs.pdu.dbcfg import pdu_db
from datetime import datetime
from pony import orm
import uuid as Uuid

class PduIndexDb(pdu_db.Entity):
    """PDU索引表"""
    _table_ = "pdu_index"
    uuid = orm.Required(Uuid.UUID, unique=True, nullable=False)  # 设备唯一识别码 唯一且不能为空
    dev_key =  orm.Optional(str, max_len=128, nullable=True, default=None) # 设备key 设备关键字用来在数据库中区别不同的设备
    createtime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP') # 创建时间
    updatetime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP')  # 更新时间

    uut = orm.Optional("PduUutDb", nullable=True, default=None, reverse="pdu_id")
    dev = orm.Optional("PduDevDb", nullable=True, default=None, reverse="pdu_id") # 设备配置索引
    hda = orm.Set("PduHdaDb", nullable=True, default=None,  reverse="pdu_id")
    data = orm.Set("PduDataDb", nullable=True, default=None, reverse="pdu_id")
    alarm = orm.Set("PduAlarmDb", nullable=True, default=None, reverse="pdu_id")
    event = orm.Set("PduEventDb", nullable=True, default=None, reverse="pdu_id")
    threshold = orm.Set("PduThresholdDb", nullable=True, default=None, reverse="pdu_id")

class PduIndexSql:
    """PDU索引表的操作类"""
    def __init__(self):
        self.mUuidKeyDict = {}  # 用来存储其它表中的pdu_id UUID对应的主键

    def insert(self, uid):
        db = PduIndexDb.get(uuid=uid)
        if db is None:
            db = PduIndexDb(uuid=uid)
            db.flush()
        self.mUuidKeyDict[uid] = db
        return db

    def set(self, uid, key):
        db = self.get(uid)
        db.dev_key = key
        db.updatetime = datetime.now()

    def get(self, uid):
        db = self.mUuidKeyDict.get(uid)
        if db is None:
            db = self.insert(uid)
            self.mUuidKeyDict[uid] = db
        return db

