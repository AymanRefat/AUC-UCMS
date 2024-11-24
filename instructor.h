#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <QString>

// No need to complicate things
class Instructor
{
private:
    QString name, department;
public:
    Instructor(QString name, QString department);

    // Getters
    QString get_name() const;
    QString get_department() const;
};

#endif // INSTRUCTOR_H
