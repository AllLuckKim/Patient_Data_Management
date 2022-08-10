#include "dialogsave.h"
#include "qsqlrecord.h"
#include "ui_dialogsave.h"
#include <QtSql/QSqlQuery>
#include <QApplication>
#include <QDebug>
#include <QDate>



DialogSave::DialogSave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSave)
{

    ui->setupUi(this);
    qdate = new QDate;


   // QSqlQuery query;
   // query.exec("SELECT * FROM employee WHERE pnt_id =="+ ui->pidEdit_2->text());
   // ui->nameEdit_2->setText(query.value(0).toString());
    qdate->setDate(2000,01,01);


    ui->addBtn_2->setEnabled(false);
    QRegularExpression e("[0-9]{0,9}");
    QRegularExpressionValidator *intValidator = new QRegularExpressionValidator(e, this);
    ui->pidEdit_2->setValidator(intValidator);
    ui->pumEdit_2->setValidator(intValidator);
    QRegularExpression ei("[0-9]{0,4}");
    QRegularExpressionValidator *intVal = new QRegularExpressionValidator(ei, this);
    ui->phoneEdit_3->setValidator(intVal);
    ui->phoneEdit_4->setValidator(intVal);
    ui->telEdit_3->setValidator(intVal);
    ui->telEdit_4->setValidator(intVal);
    QRegularExpression exp("[ㄱ-힣a-zA-Z]{0,6}");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(exp, this);
    ui->nameEdit_2->setValidator(validator);

    QRegularExpression ex("[0-9ㄱ-힣a-zA-Z]{0,6}");
    QRegularExpressionValidator *val = new QRegularExpressionValidator(ex, this);
    ui->docEdit_2->setValidator(val);
    QRegularExpression exi("[0-9a-zA-Z]{0,20}");
    QRegularExpressionValidator *vali = new QRegularExpressionValidator(exi, this);
    ui->mailEdit_3->setValidator(vali);



}

DialogSave::~DialogSave()
{
    delete ui;
}
void DialogSave::ReceiveID(QString data)
{
     ui->pidEdit_2->setText(data);
}
void DialogSave::ReceiveName(QString data)
{
     ui->nameEdit_2->setText(data);
}
void DialogSave::ReceiveBirth(QDate data)
{
     ui->birthEdit_2->setDate(data);
}
void DialogSave::ReceivePnum(QString data)
{
     ui->pumEdit_2->setText(data);
}
void DialogSave::ReceivePhone(QString data)
{
     if(!data.isEmpty())
     {
         QStringList list = data.split("-");
         ui->phoneCombobox_2->setCurrentText(list[0]);
         ui->phoneEdit_3->setText(list[1]);
         ui->phoneEdit_4->setText(list[2]);

     }
}
void DialogSave::ReceiveTel(QString data)
{
     if(!data.isEmpty())
     {
         QStringList list = data.split("-");
         ui->telCombobox_2->setCurrentText(list[0]);
         ui->telEdit_3->setText(list[1]);
         ui->telEdit_4->setText(list[2]);
     }
}
void DialogSave::ReceiveDoc(QString data)
{
     ui->docEdit_2->setText(data);
}
void DialogSave::ReceiveMail(QString data)
{
    if(!data.isEmpty())
    {
        QStringList list = data.split("@");
        ui->mailcomboBox_2->setCurrentText("직접입력");
        ui->mailEdit_3->setText(list[0]);
        ui->mailEdit_4->setText(list[1]);
    }
    else
    {
        ui->mailEdit_4->setText(ui->mailcomboBox_2->currentText());
    }
}
void DialogSave::ReceiveCvisit(QDate data)
{
     ui->cvisitEdit_2->setDate(data);
}
void DialogSave::ReceiveFvisit(QDate data)
{
     ui->fvisitEdit_2->setDate(data);
}
void DialogSave::ReceiveAddr(QString data)
{
     ui->addrEdit_2->setPlainText(data);
}

void DialogSave::on_addBtn_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("환자 정보 수정");
    msgBox.setText("환자 정보를 수정하시겠습니까?");
    QAbstractButton *myYesButton = msgBox.addButton("예", QMessageBox::YesRole);
    QAbstractButton *myNoButton = msgBox.addButton("아니오", QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();

    if(msgBox.clickedButton() == myYesButton){
        QSqlQuery query;
        query.exec("DELETE FROM TB_PATIENT_INFO WHERE pnt_uid = " + (ui->pidEdit_2->text()) );
        query.prepare("INSERT INTO TB_PATIENT_INFO (pnt_uid, pnt_name, resi_no, birth_date, hp_no, home_tel, email, home_addr, registration_date, lastvisit_date, doctor_uid)"
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(ui->pidEdit_2->text());
        query.addBindValue(ui->nameEdit_2->text());
        query.addBindValue(ui->pumEdit_2->text());
        query.addBindValue(ui->birthEdit_2->text());
        query.addBindValue(ui->phoneCombobox_2->currentText()+"-"+ui->phoneEdit_3->text()+"-"+ui->phoneEdit_4->text());
        query.addBindValue(ui->telCombobox_2->currentText()+"-"+ui->telEdit_3->text()+"-"+ui->telEdit_4->text());
        query.addBindValue((ui->mailEdit_3->text())+"@"+(ui->mailEdit_4->text()));
        query.addBindValue(ui->addrEdit_2->toPlainText());
        query.addBindValue(ui->fvisitEdit_2->text());
        query.addBindValue(ui->cvisitEdit_2->text());
        query.addBindValue(ui->docEdit_2->text());

        if(!query.exec())
        {
            QMessageBox::critical(this,"정보 수정 실패","환자 데이터 수정에 실패하였습니다.");
        }
        else
        {
            QMessageBox::information(this,"정보 수정 성공","환자 데이터 수정에 성공하였습니다.");
            ui->pidEdit_2->clear();
            ui->nameEdit_2->clear();
            ui->pumEdit_2->clear();
            ui->birthEdit_2->setDate(*qdate);
            ui->phoneEdit_3->clear();
            ui->telEdit_3->clear();
            ui->mailEdit_3->clear();
            ui->phoneEdit_4->clear();
            ui->telEdit_4->clear();
            ui->mailEdit_4->clear();
            ui->addrEdit_2->clear();
            ui->fvisitEdit_2->setDate(qdate->currentDate());
            ui->cvisitEdit_2->setDate(qdate->currentDate());
            ui->docEdit_2->clear();
        }


        query.exec();
    }



}


void DialogSave::on_closeBtn_2_clicked()
{
   close();
}


void DialogSave::on_pidEdit_2_textChanged(const QString &arg1)
{
    if((ui->pidEdit_2->text() != "")&&(ui->nameEdit_2->text() != ""))
    {
        ui->addBtn_2->setEnabled(true);
    }
    else
        ui->addBtn_2->setEnabled(false);
}





void DialogSave::on_nameEdit_2_textChanged(const QString &arg1)
{
    if((ui->pidEdit_2->text() != "")&&(ui->nameEdit_2->text() != ""))
    {
        ui->addBtn_2->setEnabled(true);
    }
    else
        ui->addBtn_2->setEnabled(false);

}








void DialogSave::on_mailcomboBox_2_currentTextChanged(const QString &arg1)
{
    if((ui->mailcomboBox_2->currentText())=="직접입력")
    {
        ui->mailEdit_4->clear();
        ui->mailEdit_4->setEnabled(true);
    }
    else
    {
        ui->mailEdit_4->setEnabled(false);
        ui->mailEdit_4->setText((ui->mailcomboBox_2->currentText()));
    }


}
