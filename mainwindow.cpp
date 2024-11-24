#include "mainwindow.h"
<<<<<<< HEAD
#include "adminloginpage.h"
#include "dashboard.h"
=======
#include "courserepository.h"
#include "enrollmentrepository.h"
>>>>>>> 311f9b3eaed054852c497c6ca96ae403788ebe90
#include "eventrepository.h"
#include "student.h"
#include "ui_mainwindow.h"
<<<<<<< HEAD
#include "register.h"

=======
#include "authenticationrepository.h"
>>>>>>> 311f9b3eaed054852c497c6ca96ae403788ebe90

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


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

