#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtSql/QSqlQuery>
#include <QApplication>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QtWidgets>
#include <QModelIndex>
#include <QPixmap>
#include <QSize>
#include <QSqlRelationalDelegate>
#include <dialog.h>
#include <dialogsave.h>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_addBtn_clicked();

    void on_delBtn_clicked();

    void on_saveBtn_clicked();


    void on_searchBtn_clicked();

    void on_searchEdit_returnPressed();

    void on_pidEdit_textChanged(const QString &arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);
signals: // 추가
    void SendID(QString data);
    void SendName(QString data);
    void SendBirth(QDate data);
    void SendPnum(QString data);
    void SendPhone(QString data);
    void SendTel(QString data);
    void SendDoc(QString data);
    void SendMail(QString data);
    void SendCvisit(QDate data);
    void SendFvisit(QDate data);// 추가
    void SendAddr(QString data);// 추가
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    Dialog *dialog;
    DialogSave *dialogsave;
    QDate *qdate;
    bool *check;
protected:
    void closeEvent(QCloseEvent *);

};
#endif // MAINWINDOW_H
