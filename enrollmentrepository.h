#ifndef ENROLLMENTREPOSITORY_H
#define ENROLLMENTREPOSITORY_H

#include "quuid.h"
#include "utils.h"
#include "instructor.h"
#include <QSet>

class EnrollmentRepository
{
private:
    QHash<QUuid, class Instructor> instructors;
    QSet<QUuid> courses, events;
public:
    EnrollmentRepository();

    // Logic

    // Preconditions: none
    // Postconditions: Data is loaded from the file
    void load(QString student_id);

    // Preconditions: none
    // Postconditions: Data is stored in the file
    void store(QString student_id);

    // Precondition: student_id and course_id are valid
    // Postcondition: student_id is enrolled in course_id (only validates if student exists)
    void enroll_in_course(QString student_id, QUuid course_id);

    // Precondition: student_id and course_id are valid
    // Postcondition: student_id is removed from course_id (only validates if student exists)
    void drop_course(QString student_id, QUuid course_id);

    // Precondition: student_id and event_id are valid
    // Postcondition: student_id is enrolled in event_id (only validates if student exists)
    void enroll_in_event(QString student_id, QUuid event_id);

    // Precondition: student_id and event_id are valid
    // Postcondition: student_id is removed from event_id (only validates if student exists)
    void drop_event(QString student_id, QUuid event_id);

    // Getters

    // Precondition: student_id is valid
    // Postcondition: returns a list of course ids that student_id is enrolled in
    QList<QUuid> get_student_courses(QString student_id);

    // Precondition: student_id is valid
    // Postcondition: returns a list of event ids that student_id is enrolled in
    QList<QUuid> get_student_events(QString student_id);

    // (Not the right place, but for now)
    QHash<QUuid, class Instructor>& get_instructors();
    class Instructor get_instructor(QUuid id);
    class Instructor get_instructor(QString name);


private:
    void load(QString student_id, ActivityType type);
    void store(QString, ActivityType);
    void enroll(QString student_id, QUuid activityId, ActivityType type);
    void drop(QString student_id, QUuid activityId, ActivityType type);
    QList<QUuid> get_student_activities(QString student_id, ActivityType type);
};

#endif // ENROLLMENTREPOSITORY_H
