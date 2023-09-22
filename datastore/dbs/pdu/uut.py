from dbs.pdu.dbcfg import pdu_db
from datetime import datetime
from sql import PduSqlObj
from pony import orm

class PduUutDb(pdu_db.Entity):
    """PDU位置信息表"""
    _table_ = "pdu_uut"
    pdu_id = orm.Required("PduIndexDb", column="pdu_id", reverse="uut") # 一对一
    room_name = orm.Optional(str, max_len=64, nullable=True, default=None)  # 机房名称
    dev_position = orm.Optional(str, max_len=64, nullable=True, default=None) # 设备位置
    dev_type = orm.Optional(str, max_len=64, nullable=True, default=None) # 设备型号
    dev_name = orm.Optional(str, max_len=64, nullable=True, default=None)  # 设备名称
    dev_sn = orm.Optional(str, max_len=64, nullable=True, default=None)  # 序列号
    qrcode = orm.Optional(str, max_len=256, nullable=True, default=None)  # 二维码内容
    createtime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP') # 创建时间
    updatetime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP')  # 更新时间



class PduUutSql(PduSqlObj):
    """PDU位置信息表操作类"""

    def __init__(self):
        self.mObj = PduUutDb




