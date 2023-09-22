from dbs.pdu.dbcfg import pdu_db
from datetime import datetime
from sql import PduSqlObj
from pony import orm

class PduAlarmDb(pdu_db.Entity):
    """PDU报警记录表"""
    _table_ = "pdu_alarm"
    pdu_id = orm.Required("PduIndexDb", column="pdu_id", reverse="alarm")  # 多对一
    alarm_status = orm.Required(str, max_len=48, nullable=False) # 报警类型
    alarm_content = orm.Required(str, max_len=128, nullable=False) # 报警内容
    createtime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP')  # 创建时间


class PduAlarmSql(PduSqlObj):
    """PDU报警记录操作类"""
    def __init__(self):
        self.mObj = PduAlarmDb

    def insert(self, id, alarm, msg):
        PduAlarmDb(pdu_id = id, alarm_status = alarm, alarm_content = msg)

