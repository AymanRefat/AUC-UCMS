#include "register.h"
#include "admin_page.h"
#include "ui_register.h"
#include "mainwindow.h"
#include "student.h"
#include "admin.h"

Register::Register(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    hide();
    MainWindow*mainwindow= new MainWindow(this);
    mainwindow->show();
}


void Register::on_pushButton_register_clicked()
{
    // Get the values from the input fields
    QString username = ui->lineEdit__R_username->text();
    QString password = ui->lineEdit_R_password->text();
    QString first_name = ui->lineEdit__R_firstname->text();
    QString last_name = ui->lineEdit__R_lastname->text();
    QString email = ui->lineEdit__R_email->text();
    QString phone_number = ui->lineEdit__R_phone->text();
    QString address = ui->lineEdit__R_address->text();
    QString type = ui->comboBox_user_type->currentText();

    // Create a new user
    if (type == "Student") {
        // Create a new student
        class Student* student = new class Student(
            QUuid::createUuid(), username, password, first_name, last_name, email, phone_number, address, 0.0, ClassStanding::Freshman
            );
        // Call APP to create student
        delete student; // Just for now
    } else {
        // Create a new admin
        class Admin *admin = new class Admin(
            QUuid::createUuid(), username, password, first_name, last_name, email, phone_number, address, AdminRole::Instructor, 3000
            );
        // Call APP to create admin
        delete admin; // Just for now
    }
}


void Register::on_pushButton_login_page_clicked()
{
    hide();
    MainWindow *mainwindow= new MainWindow(this);
    mainwindow->show();
}

