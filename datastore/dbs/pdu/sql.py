from datetime import datetime
from pony.orm import exists


class PduSqlObj:
    """PDU配置表操作类"""

    def __init__(self):
        self.mObj = None

    def add(self, id):
        db = self.mObj.get(pdu_id=id)
        if db is None:
            db = self.mObj(pdu_id=id)
            # db.createtime = datetime.now()
            db.flush()
        return db

    def get(self, id):
        return self.mObj.get(pdu_id=id) or self.add(id)

    def set(self, id, key, value):
        db = self.get(id)
        setattr(db, key, value)
        # if exists(self.mObj.updatetime):
        db.updatetime = datetime.now()

    def settings(self, id, dictionary):
        for key, value in dictionary.items():
            self.set(id, key, value)
