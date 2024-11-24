#ifndef ADMIN_PAGE_H
#define ADMIN_PAGE_H

#include <QDialog>

namespace Ui {
class Admin_page;
}

class Admin_page : public QDialog
{
    Q_OBJECT

public:
    explicit Admin_page(QWidget *parent = nullptr);
    ~Admin_page();

private slots:
    void on_pushButton_courses_clicked();

    void on_pushButton_events_clicked();

private:
    Ui::Admin_page *ui;
};

#endif // ADMIN_PAGE_H
