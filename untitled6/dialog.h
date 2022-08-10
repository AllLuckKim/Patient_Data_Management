#ifndef DIALOG_H
#define DIALOG_H

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
#include <dialog.h>
#include <QCloseEvent>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_addBtn_clicked();

    void on_closeBtn_clicked();

    void on_pidEdit_textChanged(const QString &arg1);

    void on_nameEdit_textChanged(const QString &arg1);

    void on_checkButton_clicked();

    void on_pidEdit_returnPressed();

    void on_mailcomboBox_currentTextChanged(const QString &arg1);


private:
    Ui::Dialog *ui;
    QDate *qdate;

};

#endif // DIALOG_H
