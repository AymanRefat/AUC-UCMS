#ifndef CREATEEVENTVIEW_H
#define CREATEEVENTVIEW_H

#include "qcombobox.h"
#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QUuid>

namespace Ui {
class CreateEventView;
}

class CreateEventView : public QDialog
{
    Q_OBJECT

public:
    explicit CreateEventView(QWidget *parent = nullptr);
    ~CreateEventView();

private:
    Ui::CreateEventView *ui;
    QLineEdit *titleEdit;
    QLineEdit *descriptionEdit;
    QLineEdit *locationEdit;
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    QTimeEdit *startTimeEdit;
    QTimeEdit *endTimeEdit;
    QPushButton *createButton;
    QComboBox *speakerNameCombobox;
    QLineEdit *capacityEdit;
};

#endif // CREATEEVENTVIEW_H
