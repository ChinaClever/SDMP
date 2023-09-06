from dbs.cfg.dbcfg import *
from index import PduIndex
from decimal import Decimal, ROUND_DOWN


class PduHda(db.Entity):
    """PDU历史记录表"""
    _table_ = "pdu_hda"
    pdu = orm.Required(PduIndex, column="pdu_id", reverse="hda") # 多对一

    # 1=相数据 2=回路数据 3=输出位数据 4=分组数据 5=机架数据 6=环境（温湿度）
    # 7=传感器（门禁其他传感器）  0=统计数据（总功率，总电能）
    type = orm.Required(int, size=8)

    # 1：开关 2：电压 3：电流 4：功率 5：电能 6：功率因数 7：视在功率 8：无功功率 9：电能记录
    # 10、线电压 11：温度 12：湿度 21：门禁1 22：门禁2 23：水禁 24：烟雾
    topic = orm.Required(int, size=8)

    # 1：当前值（开关状态） 2：额定值 （断开告警） 3：报警状态 4：最大值（上电延时） 5：最小值（复位延时）
    # 6：下临界值（超限断电） 7：上临界值（定时开关） 8：使能状态（开关关键设备保护） 9：最大峰值（开关当前次数）
    indexes = orm.Required(int, size=8)
    value = orm.Required(Decimal, precision=14, scale=3)
    createtime = orm.Optional(datetime, sql_default='CURRENT_TIMESTAMP')  # 创建时间



from dev import PduDev

if __name__ == "__main__":
    db.drop_table(table_name="pdu_index", if_exists=True, with_all_data=True)
    db.drop_table(table_name="pdu_hda", if_exists=True, with_all_data=True)  # 删除表，演示实体声明时用于快速清除旧表
    db.generate_mapping(create_tables=True)  # 生成实体，表和映射关系
    pass