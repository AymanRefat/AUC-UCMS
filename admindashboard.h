#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QDialog>
#include <QVBoxLayout>


namespace Ui {
class AdminDashboard;
}

class AdminDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget *parent = nullptr);
    ~AdminDashboard();

private:
    Ui::AdminDashboard *ui;
    void display();
    QVBoxLayout *frameLayout = nullptr, *frameLayout2 = nullptr;
};

#endif // ADMINDASHBOARD_H
