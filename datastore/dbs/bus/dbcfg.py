from pony import orm

db_setting = {
    "provider": "mysql",    # 声明数据库种类
    "host": "127.0.0.1",    # 数据库主机地址，也可以是域名
    "port": 3306,           # 端口
    "database": "busbar",  # 数据库名
    "user": "busbar",      # 用户名
    "password": "123456",   # 密码
    "charset": "utf8mb4",   # 字符集
}

bus_bar_db = orm.Database(**db_setting)  # 生成数据库引擎
