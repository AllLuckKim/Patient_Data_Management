#include "dialog.h"
#include "ui_dialog.h"
#include <QtSql/QSqlQuery>
#include <QApplication>
#include <QDebug>
#include <QDate>



Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    qdate = new QDate;

    ui->fvisitEdit->setDate(qdate->currentDate());
    ui->cvisitEdit->setDate(qdate->currentDate());
    ui->mailEdit_2->setText((ui->mailcomboBox->currentText()));
    qdate->setDate(2000,01,01);
    ui->addBtn->setEnabled(false);
    QRegularExpression e("[0-9]{0,9}");
    QRegularExpressionValidator *intValidator = new QRegularExpressionValidator(e, this);
    ui->pidEdit->setValidator(intValidator);
    ui->pumEdit->setValidator(intValidator);
    QRegularExpression ei("[0-9]{0,4}");
    QRegularExpressionValidator *intVal = new QRegularExpressionValidator(ei, this);
    ui->phoneEdit->setValidator(intVal);
    ui->phoneEdit_2->setValidator(intVal);
    ui->telEdit->setValidator(intVal);
    ui->telEdit_2->setValidator(intVal);
    QRegularExpression exp("[ㄱ-힣a-zA-Z]{0,6}");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(exp, this);
    ui->nameEdit->setValidator(validator);

    QRegularExpression ex("[0-9ㄱ-힣a-zA-Z]{0,6}");
    QRegularExpressionValidator *val = new QRegularExpressionValidator(ex, this);
    ui->docEdit->setValidator(val);

    QRegularExpression exi("[0-9a-zA-Z]{0,20}");
    QRegularExpressionValidator *vali = new QRegularExpressionValidator(exi, this);
    ui->mailEdit->setValidator(vali);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_addBtn_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("신규 환자 정보 저장");
    msgBox.setText("입력하신 환자를 추가하시겠습니까?");
    QAbstractButton *myYesButton = msgBox.addButton("예", QMessageBox::YesRole);
    QAbstractButton *myNoButton = msgBox.addButton("아니오", QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();

    if(msgBox.clickedButton() == myYesButton){
        QSqlQuery query;
        query.prepare("INSERT INTO TB_PATIENT_INFO (pnt_uid, pnt_name, resi_no, birth_date, hp_no, home_tel, email, home_addr, registration_date, lastvisit_date, doctor_uid)"
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(ui->pidEdit->text());
        query.addBindValue(ui->nameEdit->text());
        query.addBindValue(ui->pumEdit->text());
        query.addBindValue(ui->birthEdit->text());
        query.addBindValue(ui->phoneCombobox->currentText()+"-"+ui->phoneEdit->text()+"-"+ui->phoneEdit_2->text());
        query.addBindValue(ui->telCombobox->currentText()+"-"+ui->telEdit->text()+"-"+ui->telEdit_2->text());
        query.addBindValue((ui->mailEdit->text())+"@"+(ui->mailEdit_2->text()));
        query.addBindValue(ui->addrEdit->toPlainText());
        query.addBindValue(ui->fvisitEdit->text());
        query.addBindValue(ui->cvisitEdit->text());
        query.addBindValue(ui->docEdit->text());

        if(!query.exec())
        {
            query.exec("SELECT EXISTS(SELECT 1 FROM TB_PATIENT_INFO WHERE pnt_uid ='" + (ui->pidEdit->text())+ "')");
            qDebug() << query.lastQuery();
            if( query.next() ){
                if(query.value(0).toBool())
                    QMessageBox::critical( this , "중복 확인" , "이미 존재하는 환자 ID입니다." );
                else
                     QMessageBox::critical(this,"정보 추가 실패","환자 데이터 추가에 실패하였습니다.");
            }


        }
        else
        {

            QMessageBox::information(this,"정보 추가 성공","환자 데이터 추가에 성공하였습니다.");
            ui->pidEdit->clear();
            ui->nameEdit->clear();
            ui->pumEdit->clear();
            ui->birthEdit->setDate(*qdate);
            ui->phoneEdit->clear();
            ui->telEdit->clear();
            ui->mailEdit->clear();
            ui->addrEdit->clear();
            ui->fvisitEdit->setDate(qdate->currentDate());
            ui->cvisitEdit->setDate(qdate->currentDate());
            ui->docEdit->clear();
        }


        query.exec();
    }



}


void Dialog::on_closeBtn_clicked()
{
   close();
}


void Dialog::on_pidEdit_textChanged(const QString &arg1)
{
    if((ui->pidEdit->text() != "")&&(ui->nameEdit->text() != ""))
    {
        ui->addBtn->setEnabled(true);
    }
    else
        ui->addBtn->setEnabled(false);

}





void Dialog::on_nameEdit_textChanged(const QString &arg1)
{
    if((ui->pidEdit->text() != "")&&(ui->nameEdit->text() != ""))
    {
        ui->addBtn->setEnabled(true);
    }
    else
        ui->addBtn->setEnabled(false);
}


void Dialog::on_checkButton_clicked()
{
    if((ui->pidEdit->text())== "")
    {
        QMessageBox::warning( this , "중복 확인" , "환자 ID를 입력해주세요" );
    }
    else{
        QSqlQuery query;
        query.exec("SELECT EXISTS(SELECT 1 FROM TB_PATIENT_INFO WHERE pnt_uid ='" + (ui->pidEdit->text())+ "')");
        qDebug() << query.lastQuery();
        if( query.next() ){
            if(query.value(0).toBool())
                QMessageBox::warning( this , "중복 확인" , "이미 존재하는 환자 ID입니다." );
            else
                 QMessageBox::information( this , "중복 확인" , "사용 가능한 환자 ID입니다." );
        }
    }


}


void Dialog::on_pidEdit_returnPressed()
{
    on_checkButton_clicked();
}


void Dialog::on_mailcomboBox_currentTextChanged(const QString &arg1)
{
    if((ui->mailcomboBox->currentText())=="직접입력")
    {
        ui->mailEdit_2->clear();
        ui->mailEdit_2->setEnabled(true);
    }
    else
    {
        ui->mailEdit_2->setEnabled(false);
        ui->mailEdit_2->setText((ui->mailcomboBox->currentText()));
    }

}

