#include "activity.h"
#include <QTime>

// Constructors and destructor
Activity::Activity(QString title, QString description, QString location, int capacity, QUuid id, QDate start_date, QDate end_date, QTime start_time, QTime end_time, ActivityType type)
{
    set_title(title);
    set_description(description);
    set_location(location);
    set_id(id);
    set_capacity(capacity);
    set_start_date(start_date);
    set_end_date(end_date);
    set_start_time(start_time);
    set_end_time(end_time);
    set_type(type);
}

Activity::~Activity() {
    // Haha, Now you can't make an instance of me.
}

// Getters
QString Activity::get_title() const {
    return title;
}

QString Activity::get_description() const {
    return description;
}

QUuid Activity::get_id() const {
    return id;
}

QString Activity::get_location() const {
    return location;
}

int Activity::get_capacity() const {
    return capacity;
}

QDate Activity::get_start_date() const {
    return start_date;
}

QDate Activity::get_end_date() const {
    return end_date;
}

QTime Activity::get_start_time() const {
    return start_time;
}

QTime Activity::get_end_time() const {
    return end_time;
}

// Setters

void Activity::set_title(QString title) {
    this->title = title;
}

void Activity::set_description(QString description) {
    this->description = description;
}

void Activity::set_id(QUuid id) {
    this->id = id;
}

void Activity::set_location(QString location) {
    this->location = location;
}

void Activity::set_capacity(int capacity) {
    this->capacity = capacity;
}

void Activity::set_start_date(QDate date) {
    this->start_date = date;
}

void Activity::set_end_date(QDate date) {
    this->end_date = date;
}

void Activity::set_start_time(QTime time) {
    this->start_time = time;
}

void Activity::set_end_time(QTime time) {
    this->end_time = time;
}

void Activity::set_type(ActivityType type) {
    this->type = type;
}
