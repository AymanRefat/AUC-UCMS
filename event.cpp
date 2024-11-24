#include "event.h"

Event::Event (QString title, QString description, QString location, int capcity, QUuid id, QUuid speaker_id,
             QDate start_date, QDate end_date,
             QTime start_time, QTime end_time)
    : Activity(title, description, location, capcity, id, start_date, end_date, start_time, end_time, ActivityType::EventType) {
    set_speaker_id(speaker_id);
}

// Getters
QUuid Event::get_speaker_id() const {
    return speaker_id;
}

// Setters
void Event::set_speaker_id(QUuid speaker_id) {
    this->speaker_id = speaker_id;
}
