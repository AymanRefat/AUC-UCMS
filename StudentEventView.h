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

private:
    Ui::StudentEventView *ui;
};

#endif // STUDENTEVENTVIEW_H
