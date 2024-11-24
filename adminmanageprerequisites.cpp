#include "adminmanageprerequisites.h"
#include "ui_adminmanageprerequisites.h"

AdminManagePrerequisites::AdminManagePrerequisites(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminManagePrerequisites)
{
    ui->setupUi(this);
}

AdminManagePrerequisites::~AdminManagePrerequisites()
{
    delete ui;
}
