from dbs.pdu.dbcfg import pdu_db
from datetime import datetime
from sql import PduSqlObj
from pony import orm


class PduDevDb(pdu_db.Entity):
    """PDU配置表"""
    _table_ = "pdu_dev"
    pdu_id = orm.Required("PduIndexDb", column="pdu_id", reverse="dev") # 一对一
    run_status = orm.Optional(int, size=8, default=5)  # 运行状态 选项：0=正常 1=预警 2=告警 3= 升级 4=故障 5=离线
    dev_type = orm.Optional(str, max_len=24, nullable=False) # 设备型号
    dev_spec = orm.Optional(int, size=8, default=0) # 设备规格 1=A系列，2=B系列，3=C系列，4=D系列，
    dev_mode = orm.Optional(int, size=8, default=0) # 设备模式 0：标准 1：级联 2：机架
    line_num = orm.Optional(int, size=8, default=1) # 相数量 1=单相，3=三相
    loop_num = orm.Optional(int, size=8, default=0) # 回路数量 1 - 6
    output_num = orm.Optional(int, size=8, default=0) # 输出位数量
    cascade_addr = orm.Optional(int, size=8, default=0) # 设备级联地址
    ip_v4 = orm.Optional(str, max_len=48, nullable=True, default=None)
    ip_v6 = orm.Optional(str, max_len=48, nullable=True, default=None)
    sw_version =  orm.Optional(str, max_len=32, nullable=True, default=None) # 软件版本
    createtime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP') # 创建时间
    updatetime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP')  # 更新时间



class PduDevSql(PduSqlObj):
    """PDU配置表操作类"""

    def __init__(self):
        self.mObj = PduDevDb

