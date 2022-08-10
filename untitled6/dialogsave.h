#ifndef DIALOGSAVE_H
#define DIALOGSAVE_H


#include <QDialog>
#include <QApplication>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QtWidgets>
#include <QModelIndex>
#include <QPixmap>
#include <QSize>
#include <QSqlRelationalDelegate>
#include <dialogsave.h>
#include <QCloseEvent>
namespace Ui {
class DialogSave;
}

class DialogSave : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSave(QWidget *parent = nullptr);
    ~DialogSave();

private slots:
    void on_addBtn_2_clicked();

    void on_closeBtn_2_clicked();

    void on_pidEdit_2_textChanged(const QString &arg1);

    void on_nameEdit_2_textChanged(const QString &arg1);
    void on_mailcomboBox_2_currentTextChanged(const QString &arg1);

    void ReceiveID(QString data); // 추가
    void ReceiveName(QString data);
    void ReceiveBirth(QDate data);
    void ReceivePnum(QString data);
    void ReceivePhone(QString data);
    void ReceiveTel(QString data);
    void ReceiveDoc(QString data);
    void ReceiveMail(QString data);
    void ReceiveCvisit(QDate data);
    void ReceiveFvisit(QDate data);
    void ReceiveAddr(QString data);




private:
    Ui::DialogSave *ui;
    QDate *qdate;
    QSqlTableModel *model;
};

#endif // DIALOGSAVE_H
