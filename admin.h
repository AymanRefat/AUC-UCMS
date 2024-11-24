#ifndef UCMS_ADMIN_H
#define UCMS_ADMIN_H

#include "user.h"
#include "utils.h"

class Admin : public User {
    AdminRole role;
    double salary;
public:
    Admin(QUuid id, QString username, QString password, QString first_name, QString last_name, QString email, QString address, QString phone, AdminRole role,  double salary);

    // Getters
    AdminRole get_role() const ;
    double get_salary() const ;

    // Setters
    void set_role(AdminRole type);
    void set_salary(double salary);

};




#endif //UCMS_ADMIN_H
