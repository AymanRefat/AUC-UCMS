#include "StudentEventView.h"
#include "app.h"
#include "event.h"
#include "ui_StudentEventView.h"
#include "utils.h"
#include <QMessageBox>

extern App *app;

StudentEventView::StudentEventView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StudentEventView)
{
    ui->setupUi(this);

    populateEventTable();
    load_logout_button(this);
}

void StudentEventView::populateEventTable() {
    // Example event data   ( replace with the actual events data)
    QList<Event*> events = app->event_manager->get_all();
    qDebug() << "From events view: " <<  events.size();

    ui->Event_Table->setRowCount(events.size()); // dynamically set the table

    for (int row = 0; row < events.size(); ++row) {

        ui->Event_Table->setItem(row, 0, new QTableWidgetItem(events[row]->get_title()));
        ui->Event_Table->setItem(row, 1, new QTableWidgetItem(events[row]->get_location()));
        ui->Event_Table->setItem(row, 2, new QTableWidgetItem(QString::number(events[row]->get_capacity())));
        ui->Event_Table->setItem(row, 3, new QTableWidgetItem(events[row]->get_start_time().toString("hh:mm")));
        ui->Event_Table->setItem(row, 4, new QTableWidgetItem(events[row]->get_start_date().toString("dd:MM")));
        ui->Event_Table->setItem(row, 5, new QTableWidgetItem(app->enrollment_manager->get_instructor(events[row]->get_speaker_id()).get_name()));
        // Assign the current row the event id
        ui->Event_Table->item(row, 0)->setData(Qt::UserRole, events[row]->get_id().toString());


    }

}


StudentEventView::~StudentEventView()
{
    delete ui;
    load_logout_button(this);
}

void StudentEventView::on_RegisterEvent_Button_clicked()
{
    int selectedRow = ui->Event_Table->currentRow();
    if (selectedRow == -1) { // ensure a row is selected
        QMessageBox::warning(this, "No Selection", "Please select a event to register.");
        return;
    }

    try {
        app->enrollment_manager->enroll_in_event(app->auth_manager->get_current_user()->get_id(), QUuid(ui->Event_Table->item(selectedRow, 0)->data(Qt::UserRole).toString()));
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
        return;
    }
}

