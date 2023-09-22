from enum import Enum

class DType(Enum):
    Tg      = 0
    Line    = 1
    Loop    = 2
    Output  = 3
    Group   = 4
    Dual    = 5
    Env     = 6
    Sensor  = 7
    CabTg   = 11
    CabLine = 12
    CabLoop = 13

class DTopic(Enum):
    Relay   = 1
    Vol     = 2
    Cur     = 3
    Pow     = 4
    Ele     = 5
    PF      = 6
    ArtPow  = 7
    ReactivePow = 8
    HdaEle  = 9
    LineVol = 10
    Tem     = 11
    Hum     = 12
    Door1   = 21
    Door2   = 22
    Water   = 23
    Smoke   = 24
    Wind    = 25


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
    DPeak   = 9
    DStamp  = 10
    DHda    = 11

    UpDelay     = 4
    ResetDelay  = 5
    OverrunOff  = 6
    TimingEn    = 7
    RelayEn     = 8
    RelayCnt    = 9
    Relays      = 11
    RelayLifeEn = 12


