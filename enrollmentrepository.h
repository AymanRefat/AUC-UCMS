#ifndef ENROLLMENTREPOSITORY_H
#define ENROLLMENTREPOSITORY_H

#include "quuid.h"
#include "utils.h"
#include "instructor.h"

class EnrollmentRepository
{
public:
    EnrollmentRepository();

    // Logic

    // Precondition: student_id and course_id are valid
    // Postcondition: student_id is enrolled in course_id (only validates if student exists)
    void enroll_in_course(QUuid student_id, QUuid course_id);

    // Precondition: student_id and course_id are valid
    // Postcondition: student_id is removed from course_id (only validates if student exists)
    void drop_course(QUuid student_id, QUuid course_id);

    // Precondition: student_id and event_id are valid
    // Postcondition: student_id is enrolled in event_id (only validates if student exists)
    void enroll_in_event(QUuid student_id, QUuid event_id);

    // Precondition: student_id and event_id are valid
    // Postcondition: student_id is removed from event_id (only validates if student exists)
    void drop_event(QUuid student_id, QUuid event_id);

    // Getters

    // Precondition: student_id is valid
    // Postcondition: returns a list of course ids that student_id is enrolled in
    QList<QUuid> get_student_courses(QUuid student_id);

    // Precondition: student_id is valid
    // Postcondition: returns a list of event ids that student_id is enrolled in
    QList<QUuid> get_student_events(QUuid student_id);

    // (Not the right place, but for now)
    QList<class Instructor> get_instructors();


    // QList<QUuid> get_passed_courses(QUuid student_id);
    // QList<QUuid> get_failed_courses(QUuid student_id);
    // QList<QUuid> get_current_courses(QUuid student_id);

private:
    void enroll(QUuid student_id, QUuid activityId, ActivityType type);
    void drop(QUuid student_id, QUuid activityId, ActivityType type);
    QList<QUuid> get_student_activities(QUuid student_id, ActivityType type);
};

#endif // ENROLLMENTREPOSITORY_H
