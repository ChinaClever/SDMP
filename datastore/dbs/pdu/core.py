from uut import PduUutDb, PduUutSql
from dev import PduDevDb, PduDevSql
from hda import PduHdaDb, PduHdaSql
from data import PduDataDb, PduDataSql
from index import PduIndexDb, PduIndexSql
from alarm import PduAlarmDb, PduAlarmSql
from event import PduEventDb, PduEventSql
from threshold import PduThresholdDb, PduThresholdSql


class PduDb:
    # 使用字典存储数据库名称和对应的类
    DB_CLASSES = {
        "uut": PduUutSql,
        "dev": PduDevSql,
        "hda": PduHdaSql,
        "data": PduDataSql,
        "alarm": PduAlarmSql,
        "index": PduIndexSql,
        "event": PduEventSql,
        "threshold": PduThresholdSql
    }

    @staticmethod
    def build(db_name):
        # 在字典中查找对应的类并返回实例
        return PduDb.DB_CLASSES.get(db_name)()

    def __init__(self):
        self.uid = 0

    def index_find(self, uuid):
        db = PduDb.build("index").get(uuid)
        self.uid = db.id

    def uut_set(self, key, value):
        PduDb.build("uut").set(self.uid, key, value)

    def dev_set(self, key, value):
        PduDb.build("dev").set(self.uid, key, value)

    def alarm_insert(self, alarm, msg):
        PduDb.build("alarm").insert(self.uid, alarm, msg)

    def event_insert(self, type, msg):
        PduDb.build("event").insert(self.uid, type, msg)

    def hda_insert(self, type, topic, indexes, value):
        PduDb.build("hda").insert(self.uid, type, topic, indexes, value)

    def data_set(self, type, topic, indexes, value):
        PduDb.build("data").setValue(self.uid, type, topic, indexes, value)

    def threshold_set(self, type, topic, sub, indexes, value):
        PduDb.build("threshold").setValue(self.uid, type, topic, sub, indexes, value)






from pony import orm
import uuid as Uuid
from dbs.cfg.dbcfg import db

@orm.db_session
def _test_fun():
    uuid = Uuid.getnode()
    pdudb = PduDb()
    pdudb.index_find(uuid)
    pdudb.uut_set("room_name", "lzy")
    pdudb.dev_set("dev_type", "Pro")
    pdudb.alarm_insert("alarm", "luozhiyong")
    pdudb.event_insert("type", "luozhiyong")
    pdudb.hda_insert(1, 1,1,1)
    pdudb.data_set(2, 2, 2, 2)
    pdudb.threshold_set(3, 3, 3, 3,3)



if __name__ == "__main__":
    # db.drop_table(table_name="pdu_index", if_exists=True, with_all_data=True)
    # db.drop_table(table_name="pdu_uut", if_exists=True, with_all_data=True)  # 删除表，演示实体声明时用于快速清除旧表
    db.generate_mapping(create_tables=True)  # 生成实体，表和映射关系
    _test_fun()