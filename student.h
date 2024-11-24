#ifndef UCMS_STUDENT_H
#define UCMS_STUDENT_H
#include "user.h"
#include "utils.h"

class Student : public User {
    double gpa ;
    enum ClassStanding class_standing;

public :

    // Constructor
    Student(QUuid id, QString username, QString password, QString first_name, QString last_name, QString email,
            QString phone_number,QString address, double gpa, enum ClassStanding class_standing);


    // Getters
    double get_gpa() const;
    enum ClassStanding get_class_standing();


    // Setters
    void set_gpa(double);
    void set_class_standing(enum ClassStanding);

};
#endif //UCMS_STUDENT_H
