#include "mainwindow.h"
#include "adminloginpage.h"
#include "dashboard.h"
#include "eventrepository.h"
#include "student.h"
#include "ui_mainwindow.h"
<<<<<<< HEAD
#include "register.h"

=======
#include "authenticationrepository.h"
>>>>>>> d6fd7def7797670442707463f2bba1c8ac233ecd

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AuthenticationRepository authRepo;
    // authRepo.signup(new class Student(
    //     QUuid::createUuid(), "Ahmed", "123456", "Ahmed", "Ali",
    //     "somebody@something.somedomain", "12345678", "Somewhere in our vast universe", 2.2, ClassStanding::Freshman
    //     ));
    User* user = authRepo.login("Ahmed", "123456");
    qDebug() << user->get_email();
    qDebug() << user->get_firstname();
    qDebug() << user->get_lastname();
    qDebug() << user->get_phone_number();
    qDebug() << user->get_address();
    qDebug() << user->get_username();
    qDebug() << user->get_password();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Register_clicked()
{
    hide();
    Register*registerwindow= new Register(this);
    registerwindow->show();

}


void MainWindow::on_pushButton_Login_clicked()
{
    hide();
    Dashboard*Dashstudent= new Dashboard(this);
    Dashstudent->show();
}




void MainWindow::on_pushButton_adminlogin_clicked()
{
    hide(); // Hides MainWindow
    Adminloginpage* admin = new Adminloginpage(this); // Pass MainWindow as the parent
    admin->show(); // Show the admin login page
}

