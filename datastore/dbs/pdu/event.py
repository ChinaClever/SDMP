from datetime import datetime
from dbs.cfg.dbcfg import db
from sql import PduSqlObj
from pony import orm

class PduEventDb(db.Entity):
    """PDU事件记录表"""
    _table_ = "pdu_event"
    pdu_id = orm.Required("PduIndexDb", column="pdu_id", reverse="event")  # 多对一
    event_type = orm.Required(str, max_len=48, nullable=False) # 事件类型
    event_content = orm.Required(str, max_len=128, nullable=False) # 事件内容
    createtime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP')  # 创建时间



class PduEventSql(PduSqlObj):
    """PDU事件记录操作类"""
    def __init__(self):
        self.mObj = PduEventDb

    def insert(self, id, type, msg):
        PduEventDb(pdu_id = id, event_type = type, event_content = msg)



