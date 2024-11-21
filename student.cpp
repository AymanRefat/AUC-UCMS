#include "student.h"
#include <QString>

Student::Student(QString username, QString password, QString first_name, QString last_name, QString email, QString phone_number,
                 QString address, double gpa, ClassStanding class_standing) : User(username, password, first_name, last_name, email, phone_number, address) {
    set_gpa(gpa);
    set_class_standing(class_standing);
}

// Setters
void Student::set_class_standing(ClassStanding class_standing) {
    this->class_standing = class_standing;
}

void Student::set_gpa(double gpa) {
    if ( gpa < 0 || gpa > 4){
        throw std::invalid_argument("Invalid GPA");
    }
    this->gpa = gpa;
}

// Getters
double Student::get_gpa() const {
    return this->gpa;
}

ClassStanding Student::get_class_standing() {
    return this->class_standing;
}

