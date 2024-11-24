#ifndef ADMINCOURSEVIEW_H
#define ADMINCOURSEVIEW_H

#include <QDialog>

namespace Ui {
class AdminCourseView;
}

class AdminCourseView : public QDialog
{
    Q_OBJECT

public:
    explicit AdminCourseView(QWidget *parent = nullptr);
    ~AdminCourseView();

private:
    Ui::AdminCourseView *ui;
};

#endif // ADMINCOURSEVIEW_H
