from enum import Enum

class DType(Enum):
    """0:统计 1:相 2:回路 3:插接位 4:线 6:环境"""
    Tg      = 0 # 统计
    Line    = 1 # 相
    Loop    = 2 # 回路
    Outlet  = 3 # 插接位
    Wire    = 4 # 线
    Env     = 6 # 环境

class DTopic(Enum):
    """1:断路器 2:电压 3:电流 4:有功功率 5:电能 6:功率因素
    7:视在功率 8:无功功率 9:谐波含量 10:负载百分比 11:温度
    12:三相不平衡	21:剩余电流	22:零线电流
    """
    Breaker = 1 # 断路器
    Vol     = 2 # 电压
    Cur     = 3 # 电流
    Pow     = 4 # 有功功率
    Ele     = 5 # 电能
    PF      = 6 # 功率因素
    ArtPow  = 7 # 视在功率
    ReactivePow = 8 # 无功功率
    Thd     = 9 # 谐波含量
    Load    = 10 # 负载百分比
    Tem     = 11 # 温度
    Balance = 12 # 三相不平衡
    Residual= 21 # 剩余电流
    Zero    = 22 # 零线电流


class DSub(Enum):
    Size    = 0
    Value   = 1
    Rated   = 2
    Alarm   = 3
    VMax    = 4
    VMin    = 5
    VCrMin  = 6
    VCrMax  = 7
    EnAlarm = 8