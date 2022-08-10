#include "mainwindow.h"
#include "dialog.h"
#include "dialogsave.h"
#include <QtWidgets/QApplication>
#include <QDate>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Dialog dialog; // 추가
    DialogSave dialogsave;
    QDate qdate;
    bool check = true;



    w.show();
    return a.exec();
}
