#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "qboxlayout.h"
#include <QDialog>

namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void on_commandLinkButtonCourseRegister_clicked();

    void on_commandLinkButtonEventRegister_clicked();

private:
    Ui::Dashboard *ui;
    void display();

    QVBoxLayout *frameLayout = nullptr, *frameLayout2 = nullptr;
};

#endif // DASHBOARD_H
