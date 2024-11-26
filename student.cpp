#include "student.h"
#include <QString>
#include <QRandomGenerator>

Student::Student(QString id, QString username, QString password, QString first_name, QString last_name, QString email,
                 QString phone_number, double gpa, enum ClassStanding class_standing) : User(id, username, password, first_name, last_name, email, phone_number, UserType::Student) {
    set_class_standing(class_standing);

    double randomGPA = QRandomGenerator::global()->bounded(4.0);
    randomGPA = std::round(randomGPA * 100.0) / 100.0;
    set_gpa(randomGPA);
}

// Setters
void Student::set_class_standing(enum ClassStanding class_standing) {
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

enum ClassStanding Student::get_class_standing() {
    return this->class_standing;
}


