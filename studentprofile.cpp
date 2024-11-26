#include "studentprofile.h"
#include "app.h"
#include "ui_studentprofile.h"
#include "utils.h"
#include "student.h"

extern App *app;

StudentProfile::StudentProfile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StudentProfile)
{
    ui->setupUi(this);

    load_logout_button(this);

    // Load image in place of label
    QPixmap pix(getCurrentDir() + "/profile-pic.png") ;
    int w = ui->label_image->width();
    int h = ui->label_image->height();
    ui->label_image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    // Set text in place of label
    class Student *student = dynamic_cast<class Student*>(app->auth_manager->get_current_user());
    ui->label_name->setText(student->get_name());
    ui->label_email->setText(student->get_email());
    ui->label_id->setText(student->get_id());
    ui->label_username->setText(student->get_username());
    ui->label_academic_status->setText(class_standings[student->get_class_standing()] + " - Your GPA is: " + QString::number(student->get_gpa()));


}

StudentProfile::~StudentProfile()
{
    delete ui;
}
