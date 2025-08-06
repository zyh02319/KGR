#include <QApplication>
#include "view/MainWindow.h"
#include "data/DataManager.h"

int main(int argc, char *argv[])
{
    //先连接数据库
    DataManager::getInstance().connect();
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
