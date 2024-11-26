#ifndef STUDENTEVENTVIEW_H
#define STUDENTEVENTVIEW_H

#include <QDialog>

namespace Ui {
class StudentEventView;
}

class StudentEventView : public QDialog
{
    Q_OBJECT

public:
    explicit StudentEventView(QWidget *parent = nullptr);
    ~StudentEventView();

private slots:
    void on_RegisterEvent_Button_clicked();

private:
    Ui::StudentEventView *ui;
    void populateEventTable();
};

#endif // STUDENTEVENTVIEW_H
