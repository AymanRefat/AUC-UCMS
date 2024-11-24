#include "mainwindow.h"
#include "adminloginpage.h"
#include "dashboard.h"
#include "ui_mainwindow.h"
#include "register.h"


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
    Dashboard *Dashstudent= new Dashboard(this);
    Dashstudent->show();
}




void MainWindow::on_pushButton_adminlogin_clicked()
{
    hide(); // Hides MainWindow
    Adminloginpage* admin = new Adminloginpage(this); // Pass MainWindow as the parent
    admin->show(); // Show the admin login page
}

