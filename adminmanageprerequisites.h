#ifndef ADMINMANAGEPREREQUISITES_H
#define ADMINMANAGEPREREQUISITES_H

#include <QDialog>

namespace Ui {
class AdminManagePrerequisites;
}

class AdminManagePrerequisites : public QDialog
{
    Q_OBJECT

public:
    explicit AdminManagePrerequisites(QWidget *parent = nullptr);
    ~AdminManagePrerequisites();

private:
    Ui::AdminManagePrerequisites *ui;
};

#endif // ADMINMANAGEPREREQUISITES_H
