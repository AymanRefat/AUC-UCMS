#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "utils.h"
#include <QString>
#include <QUuid>
#include <QTime>


// Parent class of Course and Event classes //
class Activity
{
private:
    ActivityType type;
    QString title, description, location;
    QUuid id;
    int capacity;
    QDate start_date, end_date;
    QTime start_time, end_time;
public:
    // Constructors and destructor
    Activity(QString title, QString description, QString location, int capacity, QUuid id, QDate start_date, QDate end_date, QTime start_time, QTime end_time, ActivityType type);
    virtual ~Activity() = 0;

    // Getters
    QString get_title() const;
    QString get_description() const;
    QUuid get_id() const;
    QString get_location() const;
    int get_capacity() const;
    QDate get_start_date() const;
    QDate get_end_date() const;
    QTime get_start_time() const;
    QTime get_end_time() const;
    ActivityType get_type() const;

private:
    // Setters
    void set_title(QString);
    void set_description(QString);
    void set_id(QUuid);
    void set_location(QString);
    void set_capacity(int);
    void set_start_date(QDate);
    void set_end_date(QDate);
    void set_start_time(QTime);
    void set_end_time(QTime);
    void set_type(ActivityType);

    // Friend classes
    friend class ActivityRepository;
    friend class CourseRepository;
    friend class EventRepository;

};

#endif // ACTIVITY_H
