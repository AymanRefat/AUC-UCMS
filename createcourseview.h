#ifndef CREATECOURSEVIEW_H
#define CREATECOURSEVIEW_H

#include <QDialog>
#include "utils.h"
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QPushButton>
#include <QComboBox>



namespace Ui {
class CreateCourseView;
}

class CreateCourseView : public QDialog
{
    Q_OBJECT

public:
    explicit CreateCourseView(QWidget *parent = nullptr);
    ~CreateCourseView();

private:
    Ui::CreateCourseView *ui;
        QLineEdit *titleEdit;
QLineEdit *descriptionEdit;
QLineEdit *locationEdit;
QLineEdit *capacityEdit;
QComboBox *instructorNameCombobox;
QDateEdit *startDateEdit;
QDateEdit *endDateEdit;
QTimeEdit *startTimeEdit;
QTimeEdit *endTimeEdit;
QComboBox *daysComboBox;
QPushButton *createButton;
};

#endif // CREATECOURSEVIEW_H
