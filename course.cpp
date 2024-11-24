#include "course.h"

Course::Course(QString title, QString description, QString location,
               int capcity, QUuid id, QUuid instructor_id,
               QDate start_date, QDate end_date, QTime start_time, QTime end_time, QSet<Day> days)
: Activity(title, description, location, capcity, id, start_date, end_date, start_time, end_time, ActivityType::CourseType) {
    set_instructor_id(instructor_id);
    set_days(days);
}

// Getters
QUuid Course::get_instructor_id() const {
    return instructor_id;
}

QSet<Day> Course::get_days() const {
    return days;
}

// Setters
void Course::set_instructor_id(QUuid instructor_id) {
    this->instructor_id = instructor_id;
}

void Course::set_days(QSet<Day> days) {
    this->days = days;
}
