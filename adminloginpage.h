#ifndef ADMINLOGINPAGE_H
#define ADMINLOGINPAGE_H

#include <QDialog>

namespace Ui {
class Adminloginpage;
}

class Adminloginpage : public QDialog
{
    Q_OBJECT

public:
    explicit Adminloginpage(QWidget *parent = nullptr);
    ~Adminloginpage();

private slots:
    void on_pushButton_Loginadmin_clicked();

private:
    Ui::Adminloginpage *ui;
};

#endif // ADMINLOGINPAGE_H
