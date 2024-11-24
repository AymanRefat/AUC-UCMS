#include "instructor.h"

Instructor::Instructor(QString name, QString department) {
    this->name = name;
    this->department = department;
}

QString Instructor::get_name() const {
    return name;
}

QString Instructor::get_department() const {
    return department;
}
