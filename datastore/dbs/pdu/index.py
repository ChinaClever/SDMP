from dbs.cfg.dbcfg import *
import uuid as Uuid

class PduIndex(db.Entity):
    """PDU索引表"""
    _table_ = "pdu_index"
    uuid = orm.Required(Uuid.UUID, unique=True, nullable=False)  # 设备唯一识别码 唯一且不能为空
    dev_key =  orm.Optional(str, max_len=128, nullable=True, default=None) # 设备key 设备关键字用来在数据库中区别不同的设备
    createtime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP') # 创建时间
    updatetime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP')  # 更新时间

    dev = orm.Optional("PduDev", nullable=True, default=None, reverse="pdu") # 设备配置索引号
    hda = orm.Set("PduHda", nullable=True, default=None,  reverse="pdu")



