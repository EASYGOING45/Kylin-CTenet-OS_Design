#include "mainwindow.h"
#include"osdesign.h"
#include <QApplication>
#include<QSplashScreen>
#include<QDateTime>


int main(int argc, char *argv[])
{
    if(QT_VERSION >= QT_VERSION_CHECK(5,6,0))
            QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);
    QApplication a(argc, argv);
    QPixmap pix(":/images/images/back3.jpg");
    QSplashScreen screen(pix);
    screen.show();
    a.processEvents();
    screen.showMessage("OS");

    QDateTime n=QDateTime::currentDateTime();
        QDateTime now;
        do{
            now=QDateTime::currentDateTime();
        } while (n.secsTo(now)<=5);//6为需要延时的秒数

    OSDesign os;

    os.setWindowTitle("操作系统课程设计-李欢欢、刘易行");
    os.show();
//    ProcessSchedule qq;
//    qq.show();
//    MainWindow w;
//    w.show();
    screen.finish(&os);
    return a.exec();
}
