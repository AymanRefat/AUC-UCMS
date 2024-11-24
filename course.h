#ifndef COURSE_H
#define COURSE_H

#include "activity.h"
#include "quuid.h"
#include "utils.h"
#include <QString>
#include <QDate>
#include <QTime>
#include <QList>
#include <quuid.h>


class Course : public Activity
{
private:
    QUuid instructor_id;
    QSet<Day> days;
public:
    Course(
        QString title, QString description, QString location, int capcity, QUuid id,
        QUuid instructor_id, QDate start_date,
        QDate end_date, QTime start_time, QTime end_time, QSet<Day> days
    );

    // Getters
    QUuid get_instructor_id() const;
    QSet<Day> get_days() const;

// private:
    // Setters
    void set_instructor_id(QUuid);
    void set_days(QSet<Day>);

    // Friend classes
    // friend class CourseController;
    // friend class CourseRepository;

};

#endif // COURSE_H
