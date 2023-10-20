from .ormobj import SqlDatabase, MongoDatabase, OrmObj
from cabinet.models import Data, Hda, PduBox, Index
import time

import time


class PduBoxId:
    def __init__(self):
        self.index_obj = SqlDatabase(Index)
        self.pdu_box_obj = SqlDatabase(PduBox)
        self.last_query_times = {}
        self.cached_data = {}

    def _should_query(self, last_query_time):
        if last_query_time is None:
            return True
        current_time = time.time()
        elapsed_time = current_time - last_query_time
        return elapsed_time >= 30

    def _get_objects(self, index_id, obj_type):
        if obj_type == 'box':
            objects = self.pdu_box_obj.sql_box_ids(index_id)
        else:
            objects = self.pdu_box_obj.sql_pdu_ids(index_id)
        return objects

    def _get_index_ids(self):
        index_ids = self.index_obj.values_list('id')
        return index_ids

    def cabinet_ids(self):
        if 'index_ids' not in self.last_query_times or self._should_query(self.last_query_times['index_ids']):
            self.cached_data['index_ids'] = self._get_index_ids()
            self.last_query_times['index_ids'] = time.time()
        return self.cached_data.get('index_ids')

    def power_capacity(self, cabinet_id):
        cached_capacity = self.cached_data.setdefault(cabinet_id, {}).get('power_capacity')
        if cached_capacity is not None and not self._should_query(cached_capacity['query_time']):
            return cached_capacity['value']

        obj = self.index_obj.sql_find(id=cabinet_id)
        capacity = obj.pow_capacity if obj and hasattr(obj, 'pow_capacity') else 0
        self.cached_data[cabinet_id] = {'value': capacity, 'query_time': time.time()}
        return capacity

    def pdu_box(self, cabinet_id):
        cached_pdu_box = self.cached_data.setdefault(cabinet_id, {}).get('pdu_box')
        if cached_pdu_box is not None and not self._should_query(cached_pdu_box['query_time']):
            return cached_pdu_box['value']

        obj = self.index_obj.sql_find(id=cabinet_id)
        pdu_box = obj.pdu_box if obj and hasattr(obj, 'pdu_box') else 0
        self.cached_data[cabinet_id] = {'value': pdu_box, 'query_time': time.time()}
        return pdu_box

    def pdu_ids(self, index_id):
        cached_pdu_ids = self.cached_data.setdefault(index_id, {}).get('pdu_ids')
        if cached_pdu_ids is not None and not self._should_query(cached_pdu_ids['query_time']):
            return cached_pdu_ids['value']

        pdu_ids = self._get_objects(index_id, 'pdu')
        if pdu_ids is None:
            pdu_ids = []  # 如果 pdu_ids 是 None，则返回空列表

        self.cached_data[index_id] = {'value': list(set(pdu_ids)), 'query_time': time.time()}
        return list(set(pdu_ids))

    def box_ids(self, index_id):
        cached_box_ids = self.cached_data.setdefault(index_id, {}).get('box_ids')
        if cached_box_ids is not None and not self._should_query(cached_box_ids['query_time']):
            return cached_box_ids['value']

        box_ids = self._get_objects(index_id, 'box')
        if box_ids is None:
            box_ids = []  # 如果 box_ids 是 None，则返回空列表

        self.cached_data[index_id] = {'value': list(set(box_ids)), 'query_time': time.time()}
        return list(set(box_ids))


class PduBoxTg:
    def __init__(self):
        self.pdu_obj = MongoDatabase('pdu_data')
        self.box_obj = MongoDatabase('bux_box_data')

    def _get_power(self, ids, topic, obj):
        query = {
            'pdu_id' if obj == self.pdu_obj else 'box_id': {'$in': ids},
            'type': 0,
            'topic': topic
        }
        pipeline = [
            {'$match': query},
            {'$group': {'_id': None, 'total_power': {'$sum': {'$toDouble': '$value'}}}}
        ]
        result = obj.collection.aggregate(pipeline)
        total_power = next(result, {'total_power': 0})['total_power']
        return total_power

    def pdu_apparent_power(self, ids):
        return self._get_power(ids, 7, self.pdu_obj)

    def pdu_active_power(self, ids):
        return self._get_power(ids, 4, self.pdu_obj)

    def pdu_ele(self, ids):
        return self._get_power(ids, 5, self.pdu_obj)

    def box_apparent_power(self, ids):
        return self._get_power(ids, 7, self.box_obj)

    def box_active_power(self, ids):
        return self._get_power(ids, 4, self.box_obj)

    def box_ele(self, ids):
        return self._get_power(ids, 5, self.box_obj)


class CabinetManager:
    def __init__(self, ids, tgs, hda_obj, data_obj):
        self._ids = ids
        self._tgs = tgs
        self._hda_obj = hda_obj
        self._data_obj = data_obj

    def _get_default_value(self, value):
        return value if value is not None else 0

    @staticmethod
    def _calculate_pf(active_power, apparent_power):
        if apparent_power is not None and apparent_power > 0:
            return active_power / apparent_power
        return 0.0

    def _create_query_values(self, cabinet_id, ids, is_pdu):
        if is_pdu:
            power_data = {
                'apparent_power': self._tgs.pdu_apparent_power(ids),
                'active_power': self._tgs.pdu_active_power(ids),
                'ele': self._tgs.pdu_ele(ids)
            }
        else:
            power_data = {
                'apparent_power': self._tgs.box_apparent_power(ids),
                'active_power': self._tgs.box_active_power(ids),
                'ele': self._tgs.box_ele(ids)
            }

        power_capacity = self._ids.power_capacity(cabinet_id)

        values = {
            'apparent_power': self._get_default_value(power_data['apparent_power']),
            'active_power': self._get_default_value(power_data['active_power']),
            'overhead': round(power_capacity - self._get_default_value(power_data['apparent_power']), 3),
            'ele': self._get_default_value(power_data['ele']),
            'pf': round(self._calculate_pf(power_data['active_power'], power_data['apparent_power']), 2)
        }

        query = {'cabinet_id': cabinet_id}
        return query, values

    def _update_orm(self, cabinet_id, ids, is_pdu):
        query, values = self._create_query_values(cabinet_id, ids, is_pdu)
        query_value = {**query, **values}

        if not self._data_obj.mongo_is_exist(query_value, values['apparent_power'], 0):
            self._data_obj.sql_update(cabinet_id, **values)

        query_value.pop('ele', None)
        res = self._data_obj.mongo_is_exist(query_value, values['apparent_power'], 0.1)
        self._data_obj.mongo_update(query, values)
        return res

    def _append_orm(self, cabinet_id, ids, is_pdu):
        query, values = self._create_query_values(cabinet_id, ids, is_pdu)
        query_value = {**query, **values}
        query_value.pop('overhead', None)
        self._hda_obj.sql_insert(**query_value)

    def update_data(self, cabinet_id):
        pdu_ids = self._ids.pdu_ids(cabinet_id)
        box_ids = self._ids.box_ids(cabinet_id)
        pdu_box = self._ids.pdu_box(cabinet_id)

        print(pdu_ids)

        if pdu_ids and pdu_box == 0:
            res = self._update_orm(cabinet_id, pdu_ids, True)
            if not res:
                self._append_orm(cabinet_id, pdu_ids, True)
        elif box_ids:
            res = self._update_orm(cabinet_id, box_ids, False)
            if not res:
                self._append_orm(cabinet_id, box_ids, False)

    def append_hda(self, cabinet_id):
        pdu_ids = self._ids.pdu_ids(cabinet_id)
        box_ids = self._ids.box_ids(cabinet_id)
        pdu_box = self._ids.pdu_box(cabinet_id)

        if pdu_ids and pdu_box == 0:
            self._append_orm(cabinet_id, pdu_ids, True)
        elif box_ids:
            self._append_orm(cabinet_id, box_ids, False)

    def cabinet_ids(self):
        return self._ids.cabinet_ids()

    def pdu_ids(self, cabinet_id):
        return self._ids.pdu_ids(cabinet_id)

    def box_ids(self, cabinet_id):
        return self._ids.box_ids(cabinet_id)


class Manager:
    def __init__(self):
        ids = PduBoxId()
        tgs = PduBoxTg()
        hda_obj = OrmObj(Hda)
        data_obj = OrmObj(Data)
        self._cabinet_manager = CabinetManager(ids, tgs, hda_obj, data_obj)

    def update_data(self):
        cabinet_ids = self._cabinet_manager.cabinet_ids()
        for cabinet_id in cabinet_ids:
            self._cabinet_manager.update_data(cabinet_id)

    def append_hda(self):
        cabinet_ids = self._cabinet_manager.cabinet_ids()
        for cabinet_id in cabinet_ids:
            self._cabinet_manager.append_hda(cabinet_id)




def my_test_fun():
    manager = Manager()

    manager.update_data()
    manager.append_hda()
