#ifndef UCMS_EVENT_H
#define UCMS_EVENT_H

#include "activity.h"
#include <QDateTime>


class Event : public Activity
{
private:
    QUuid speaker_id;
public:
    Event(QString title, QString description, QString location, int capcity, QUuid id,
        QUuid speaker_id, QDate start_date, QDate end_date,
          QTime start_time, QTime end_time);

    // Getters
    QUuid get_speaker_id() const;

// private:
    // Setters
    void set_speaker_id(QUuid speaker_id);
};

#endif //UCMS_EVENT_H


/*

1) IMPLEMENTATION.

2) SERVICES:
Authorization => Sign up, Sign in, Sign out, Modify account information.
Course => Create, Modify, Delete, Get, Enroll, Drop.
Event => Create, Modify, Delete, Get, Enroll, Drop.

3) DATA FILES:
users-auth.csv => username, id, email, password
users-profile => id, first_name, last_name, phone_number, address, type
students.csv => id, gpa, class_standing
admins.csv => id, title (Mr, Mrs, Dr, Prof, etc), department (IT, HR, etc), position (TA, Instructor, etc).
courses.csv => id, title, description, instructor_id, capacity, start_date, end_date, days, time, location.
events.csv => id, title, description, date_time, capacity, location.

*/
