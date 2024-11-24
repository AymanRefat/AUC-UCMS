#include "adminloginpage.h"
#include "admin_page.h" // Ensure this header is included if Admin_page is defined elsewhere
#include "ui_adminloginpage.h"

Adminloginpage::Adminloginpage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Adminloginpage)
{
    ui->setupUi(this);
}

Adminloginpage::~Adminloginpage()
{
    delete ui;
}

void Adminloginpage::on_pushButton_Loginadmin_clicked()
{
    hide();                                     // Hide the current login page
    Admin_page *adminpa = new Admin_page(this); // Create an instance of Admin_page
    adminpa->show();                            // Show the admin page
}
