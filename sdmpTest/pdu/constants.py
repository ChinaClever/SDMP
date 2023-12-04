

PDU_TYPE_LIST = {
    0: 'Tg',
    1: 'Line',
    2: 'Loop',
    3: 'Output',
    4: 'Group',
    5: 'Dual',
    6: 'Env',
    7: 'Sensor',
    11: 'CabTg',
    12: 'CabLine',
    13: 'CabLoop',
}


PDU_TOPIC_LIST = {
    1: 'Relay',
    2: 'Vol',
    3: 'Cur',
    4: 'Pow',
    5: 'Ele',
    6: 'PF',
    7: 'ArtPow',
    8: 'ReactivePow',
    9: 'HdaEle',
    10: 'LineVol',
    11: 'Tem',
    12: 'Hum',

    21: 'Door1',
    22: 'Door2',
    23: 'Water',
    24: 'Smoke',
    25: 'Wind',
}


PDU_SUB_LIST = {
    0: 'Size',
    1: 'Value',
    2: 'Rated',
    3: 'Alarm',
    4: 'VMax',
    5: 'VMin',
    6: 'VCrMin',
    7: 'VCrMax',
    8: 'EnAlarm',
    9: 'DPeak',
    10: 'DStamp',
    11: 'DHda',
}

PDU_RELAY_LIST = {
    4: 'UpDelay',
    5: 'ResetDelay',
    6: 'OverrunOff',
    7: 'TimingEn',
    8: 'RelayEn',
    9: 'RelayCnt',
    11: 'Relays',
    12: 'RelayLifeEn',
}






