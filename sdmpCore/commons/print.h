#ifndef COMMON_H
#define COMMON_H
#include "msgbox.h"

void cm_mdelay(int msec);
bool cm_pingNet(const QString& ip);
bool cm_isDigitStr(const QString &src);
bool cm_isIPaddress(const QString& ip);

QString cm_execute(const QString &cmd);
QString cm_ByteArrayToHexStr(uchar *buf, int len);
QString cm_ByteArrayToHexStr(const QByteArray &array);
QString cm_ByteArrayToUcharStr(const QByteArray &array);

#ifndef cout
#define cout qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << "[" << __FILE__ << ":" << Q_FUNC_INFO << ":" << __LINE__ << "]"
#endif

#endif // COMMON_H
