#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"

#include <QtSql/QSqlQuery>
#include <QApplication>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QDate>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    dialog = new Dialog ;
    dialogsave = new DialogSave;
    qdate = new QDate;
    qdate->setDate(2000,01,01);
    QRegularExpression e("[0-9]{0,9}");
    QRegularExpressionValidator *intValidator = new QRegularExpressionValidator(e, this);

    ui->pidEdit->setValidator(intValidator);
    ui->pumEdit->setValidator(intValidator);
    QRegularExpression exp("[ㄱ-힣a-zA-Z]{0,6}");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(exp, this);

    ui->nameEdit->setValidator(validator);


    QRegularExpression ex("[0-9ㄱ-힣a-zA-Z]{0,6}");
    QRegularExpressionValidator *val = new QRegularExpressionValidator(ex, this);
    ui->docEdit->setValidator(val);





    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->searchEdit->setClearButtonEnabled(true);
    ui->comboBox->addItem("환자 ID");
    ui->comboBox->addItem("이름");
    ui->comboBox->addItem("환자 번호");
    ui->comboBox->addItem("전화 번호(뒷 4자리)");
    ui->comboBox->addItem("담당자");



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<QCoreApplication::libraryPaths();

    QString file = QFileDialog::getOpenFileName(this,"파일 선택","C:\\","Files(*.db)");
    qDebug()<<file;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");


    if(file!="")
    {

        db.setDatabaseName(file);
        db.open();
        QSqlQuery query;
        query.exec("SELECT COUNT(*) FROM sqlite_master WHERE type = 'table' AND name = 'TB_PATIENT_INFO'");
        if(query.next())
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model -> setTable("TB_PATIENT_INFO");
            ui->tableView->setModel(model);
            model->select();

            QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
            mapper->setModel(model);
            mapper->addMapping(ui->nameEdit, model->fieldIndex("pnt_name"));
            mapper->addMapping(ui->pidEdit, model->fieldIndex("pnt_uid"));
            mapper->addMapping(ui->birthEdit, model->fieldIndex("birth_date"));
            mapper->addMapping(ui->pumEdit, model->fieldIndex("resi_no"));
            mapper->addMapping(ui->phoneEdit, model->fieldIndex("hp_no"));
            mapper->addMapping(ui->telEdit, model->fieldIndex("home_tel"));
            mapper->addMapping(ui->mailEdit, model->fieldIndex("email"));
            mapper->addMapping(ui->addrEdit, model->fieldIndex("home_addr"));
            mapper->addMapping(ui->fvisitEdit, model->fieldIndex("registration_date"));
            mapper->addMapping(ui->cvisitEdit, model->fieldIndex("lastvisit_date"));
            mapper->addMapping(ui->docEdit, model->fieldIndex("doctor_uid"));

            connect(ui->tableView->selectionModel(),
                    &QItemSelectionModel::currentRowChanged,
                    mapper,
                    &QDataWidgetMapper::setCurrentModelIndex
                    );
            if(query.value(0).toBool())
            {
                ui->addBtn->setEnabled(true);
                ui->searchBtn->setEnabled(true);
                ui->searchEdit->setEnabled(true);
                model->setFilter("");

            }
            else
            {
                QMessageBox::critical(this,"파일 형식 오류","DB파일의 형식이 맞지 않습니다.");
                ui->pidEdit->clear();
                ui->nameEdit->clear();
                ui->pumEdit->clear();
                ui->birthEdit->setDate(*qdate);
                ui->phoneEdit->clear();
                ui->telEdit->clear();
                ui->mailEdit->clear();
                ui->addrEdit->clear();
                ui->fvisitEdit->setDate(*qdate);
                ui->cvisitEdit->setDate(*qdate);
                ui->docEdit->clear();
                ui->addBtn->setEnabled(false);
                ui->searchBtn->setEnabled(false);
                ui->searchEdit->setEnabled(false);
                model->setFilter("");

            }
        }

    }
    else
    {
        QMessageBox::critical(this,"파일 열리지 않음","데이터 파일이 선택되지 않았습니다.");

//        model = new QSqlTableModel(this);
//        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//        model -> setTable("TB_PATIENT_INFO");
//        ui->tableView->setModel(model);
//        model->select();
       ui->tableView->show();
    }


}


void MainWindow::on_addBtn_clicked()
{

    dialog->show();


}


void MainWindow::on_delBtn_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("환자 정보 삭제");
    msgBox.setText("입력하신 환자를 삭제하시겠습니까?");
    QAbstractButton *myYesButton = msgBox.addButton("예", QMessageBox::YesRole);
    QAbstractButton *myNoButton = msgBox.addButton("아니오", QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();


    if(msgBox.clickedButton() == myYesButton){
        QSqlQuery query;

        query.exec("DELETE FROM TB_PATIENT_INFO WHERE pnt_uid = " + (ui->pidEdit->text()) );

        ui->tableView->setModel(model);

        ui->pidEdit->clear();
        ui->nameEdit->clear();
        ui->pumEdit->clear();
        ui->birthEdit->setDate(*qdate);
        ui->phoneEdit->clear();
        ui->telEdit->clear();
        ui->mailEdit->clear();
        ui->addrEdit->clear();
        ui->fvisitEdit->setDate(*qdate);
        ui->cvisitEdit->setDate(*qdate);
        ui->docEdit->clear();
        QMessageBox::information(this,"정보 삭제","환자 데이터가 삭제되었습니다.");
        model->setFilter("");

    }

}


void MainWindow::on_saveBtn_clicked()
{

    connect(this,SIGNAL(SendID(QString)),dialogsave,SLOT(ReceiveID(QString)));
    connect(this,SIGNAL(SendName(QString)),dialogsave,SLOT(ReceiveName(QString)));    //connect(this,SIGNAL(Send3(QString)),dialogsave,SLOT(Receive(QString)));
    connect(this,SIGNAL(SendBirth(QDate)),dialogsave,SLOT(ReceiveBirth(QDate)));
    connect(this,SIGNAL(SendPnum(QString)),dialogsave,SLOT(ReceivePnum(QString)));
    connect(this,SIGNAL(SendPhone(QString)),dialogsave,SLOT(ReceivePhone(QString)));
    connect(this,SIGNAL(SendTel(QString)),dialogsave,SLOT(ReceiveTel(QString)));
    connect(this,SIGNAL(SendDoc(QString)),dialogsave,SLOT(ReceiveDoc(QString)));
    connect(this,SIGNAL(SendMail(QString)),dialogsave,SLOT(ReceiveMail(QString)));
    connect(this,SIGNAL(SendCvisit(QDate)),dialogsave,SLOT(ReceiveCvisit(QDate)));
    connect(this,SIGNAL(SendFvisit(QDate)),dialogsave,SLOT(ReceiveFvisit(QDate)));
    connect(this,SIGNAL(SendAddr(QString)),dialogsave,SLOT(ReceiveAddr(QString)));

    emit SendID(ui->pidEdit->text());
    emit SendName(ui->nameEdit->text());
    emit SendBirth(ui->birthEdit->date());
    emit SendPnum(ui->pumEdit->text());
    emit SendPhone(ui->phoneEdit->text());
    emit SendTel(ui->telEdit->text());
    emit SendDoc(ui->docEdit->text());
    emit SendMail(ui->mailEdit->text());
    emit SendCvisit(ui->cvisitEdit->date());
    emit SendFvisit(ui->fvisitEdit->date());
    emit SendAddr(ui->addrEdit->toPlainText());
    dialogsave->show();

}






void MainWindow::on_searchBtn_clicked()
{
    qdate = new QDate;
    qdate->setDate(2000,01,01);
    ui->pidEdit->clear();
    ui->nameEdit->clear();
    ui->pumEdit->clear();
    ui->birthEdit->setDate(*qdate);
    ui->phoneEdit->clear();
    ui->telEdit->clear();
    ui->mailEdit->clear();
    ui->addrEdit->clear();
    ui->fvisitEdit->setDate(*qdate);
    ui->cvisitEdit->setDate(*qdate);
    ui->docEdit->clear();
    if(ui->comboBox->currentText() == "환자 ID"  )
        model->setFilter("pnt_uid LIKE '%" + ui->searchEdit->text() + "%'");
    if(ui->comboBox->currentText() == "이름"  )
        model->setFilter("pnt_name LIKE '%" + ui->searchEdit->text() + "%'");
    if(ui->comboBox->currentText() == "환자 번호"  )
        model->setFilter("resi_no LIKE '%" + ui->searchEdit->text() + "%'");
    if(ui->comboBox->currentText() == "전화 번호(뒷 4자리)"  )
        if(ui->searchEdit->text()=="")
            model->setFilter("");
        else
            model->setFilter("hp_no LIKE '%" + ui->searchEdit->text() + "' OR home_tel LIKE '%"+ui->searchEdit->text()+"'");
    if(ui->comboBox->currentText() == "담당자"  )
        model->setFilter("doctor_uid LIKE '%" + ui->searchEdit->text() + "%'");
}


void MainWindow::on_searchEdit_returnPressed()
{
    on_searchBtn_clicked();
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    QMessageBox msgBox;
    msgBox.setWindowTitle("종료");
    msgBox.setText("프로그램을 종료하시겠습니까?");
    QAbstractButton *myYesButton = msgBox.addButton("예", QMessageBox::YesRole);
    QAbstractButton *myNoButton = msgBox.addButton("아니오", QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();
    if(msgBox.clickedButton() == myYesButton){
        event->accept();
        dialog->close();
    }else{
        event->ignore();
    }
}

void MainWindow::on_pidEdit_textChanged(const QString &arg1)
{
    if(ui->pidEdit->text() == "")
    {
        ui->delBtn->setEnabled(false);
    }
    else
        ui->delBtn->setEnabled(true);
    if(ui->pidEdit->text() == "")
    {
        ui->saveBtn->setEnabled(false);
    }
    else
        ui->saveBtn->setEnabled(true);
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(ui->comboBox->currentText() == "환자 ID"  )
    {
        ui->searchEdit->setInputMask(NULL);
        QRegularExpression exp("[0-9]{0,9}");
        QRegularExpressionValidator *comval = new QRegularExpressionValidator(exp, this);
        ui->searchEdit->setValidator(comval);
    }
    if(ui->comboBox->currentText() == "이름"  )
    {
        ui->searchEdit->setInputMask(NULL);
        QRegularExpression exp("[ㄱ-힣a-zA-Z]{0,6}");
        QRegularExpressionValidator *comval = new QRegularExpressionValidator(exp, this);
        ui->searchEdit->setValidator(comval);
    }
    if(ui->comboBox->currentText() == "환자 번호"  )
    {
        ui->searchEdit->setInputMask(NULL);
        QRegularExpression exp("[0-9]{0,9}");
        QRegularExpressionValidator *comval = new QRegularExpressionValidator(exp, this);
        ui->searchEdit->setValidator(comval);
    }
    if(ui->comboBox->currentText() == "전화 번호(뒷 4자리)"  )
    {
        QRegularExpression exp("[0-9]{0,4}");
        QRegularExpressionValidator *comval = new QRegularExpressionValidator(exp, this);
        ui->searchEdit->setValidator(comval);
    }
    if(ui->comboBox->currentText() == "담당자"  )
    {
        ui->searchEdit->setInputMask(NULL);
        QRegularExpression exp("[0-9ㄱ-힣a-zA-Z]{0,6}");
        QRegularExpressionValidator *comval = new QRegularExpressionValidator(exp, this);
        ui->searchEdit->setValidator(comval);
    }

}

