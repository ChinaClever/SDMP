from datetime import datetime
from dbs.cfg.dbcfg import db
from decimal import Decimal
from sql import PduSqlObj
from pony import orm


class PduHdaDb(db.Entity):
    """PDU历史记录表"""
    _table_ = "pdu_hda"
    pdu_id = orm.Required("PduIndexDb", reverse="hda") # 多对一

    # 1=相数据 2=回路数据 3=输出位数据 4=分组数据 5=机架数据 6=环境（温湿度）
    # 7=传感器（门禁其他传感器）  0=统计数据（总功率，总电能）
    type = orm.Required(int, size=8)

    # 1：开关 2：电压 3：电流 4：功率 5：电能 6：功率因数 7：视在功率 8：无功功率 9：电能记录
    # 10、线电压 11：温度 12：湿度 21：门禁1 22：门禁2 23：水禁 24：烟雾
    topic = orm.Required(int, size=8)

    indexes = orm.Required(int, size=8)
    value = orm.Required(Decimal, precision=14, scale=3)
    createtime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP')  # 创建时间



class PduHdaSql(PduSqlObj):
    """PDU历史记录操作类"""
    def __init__(self):
        self.mObj = PduHdaDb

    def insert(self, id, type, topic, indexes, value):
        PduHdaDb(pdu_id = id, type = type, topic = topic, indexes = indexes, value = value)

