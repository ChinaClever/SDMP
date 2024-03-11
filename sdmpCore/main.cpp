#include "mainwindow.h"
#include <QApplication>
#include <QtSingleApplication>
#include "msgbox.h"

int main(int argc, char *argv[])
{
    QtSingleApplication a("sdmp-core", argc, argv);
    if(a.isRunning()) {
        MsgBox::critical(NULL, QObject::tr("程序已运行！"));
        a.sendMessage("raise_window_noop", 1000); //4s后激活前个实例
        return EXIT_SUCCESS;
    } else {
        QCoreApplication::setOrganizationName("CLEVER");
        QCoreApplication::setOrganizationDomain("clever.com");
        QCoreApplication::setApplicationName("sdmp");
    }

    MainWindow w;
    w.show();
    return a.exec();
}
