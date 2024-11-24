#ifndef STUDENTCOURSEVIEW_H
#define STUDENTCOURSEVIEW_H

#include <QDialog>

namespace Ui {
class StudentCourseView;
}

class StudentCourseView : public QDialog
{
    Q_OBJECT

public:
    explicit StudentCourseView(QWidget *parent = nullptr);
    ~StudentCourseView();

private:
    Ui::StudentCourseView *ui;
};

#endif // STUDENTCOURSEVIEW_H
