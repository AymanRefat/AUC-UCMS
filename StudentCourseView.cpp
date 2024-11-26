#include "StudentCourseView.h"
#include "app.h"
#include "ui_StudentCourseView.h"


extern App *app;

StudentCourseView::StudentCourseView(QWidget* parent)
    : QDialog(parent), ui(new Ui::StudentCourseView) {
    ui->setupUi(this);
    // Populate the course table
    populateCourseTable();

    // Connect the register button
    connect(ui->RegisterCourse_Button, &QPushButton::clicked, this, &StudentCourseView::onRegisterButtonClicked);
    load_logout_button(this);
}


StudentCourseView::~StudentCourseView() {
    delete ui;
}

void StudentCourseView::populateCourseTable() {
    // Example course data   ( replace with the actual courses data)
    QList<Course*> courses = app->course_manager->get_all();
    qDebug() << "From courses view: " <<  courses.size();

    ui->course_Table->setRowCount(courses.size()); // dynamically set the table

    for (int row = 0; row < courses.size(); ++row) {

        qDebug() << courses[row]->get_capacity();
        ui->course_Table->setItem(row, 0, new QTableWidgetItem(courses[row]->get_title()));
        ui->course_Table->setItem(row, 1, new QTableWidgetItem(app->enrollment_manager->get_instructor(courses[row]->get_instructor_id()).get_name()));
        ui->course_Table->setItem(row, 2, new QTableWidgetItem(courses[row]->get_location()));
        ui->course_Table->setItem(row, 3, new QTableWidgetItem(courses[row]->get_start_time().toString("hh:mm")));
        ui->course_Table->setItem(row, 4, new QTableWidgetItem(QString::number(courses[row]->get_capacity())));
        // Days
        QString s = "Days: ";
        for(auto &day : courses[row]->get_days()) {
            s += days[day].left(3) + " ";
        }
        ui->course_Table->setItem(row, 5, new QTableWidgetItem(s));
        // Assign the current row the course id
        ui->course_Table->item(row, 0)->setData(Qt::UserRole, courses[row]->get_id().toString());


    }

}

void StudentCourseView::onRegisterButtonClicked() {

    int selectedRow = ui->course_Table->currentRow();
    if (selectedRow == -1) { // ensure a row is selected
        QMessageBox::warning(this, "No Selection", "Please select a course to register.");
        return;
    }

    try {
        app->enrollment_manager->enroll_in_course(app->auth_manager->get_current_user()->get_id(), QUuid(ui->course_Table->item(selectedRow, 0)->data(Qt::UserRole).toString()));
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    }
}
