#include "enrollmentrepository.h"
#include "qdir.h"
#include "utils.h"

EnrollmentRepository::EnrollmentRepository() {}

void EnrollmentRepository::load(QString student_id) {
    load(student_id, ActivityType::CourseType);
    load(student_id, ActivityType::EventType);
}

void EnrollmentRepository::store(QString student_id) {
    qDebug() << "From Store" << courses.size() << events.size();
    store(student_id, ActivityType::CourseType);
    store(student_id, ActivityType::EventType);
}

void EnrollmentRepository::enroll_in_course(QString student_id, QUuid course_id) {
    if (courses.contains(course_id))
        throw std::runtime_error("Course already enrolled");
    courses.insert(course_id);
}

void EnrollmentRepository::enroll_in_event(QString student_id, QUuid event_id) {
    if (events.contains(event_id))
        throw std::runtime_error("Event already enrolled");
    events.insert(event_id);
}

void EnrollmentRepository::drop_course(QString student_id, QUuid course_id) {
    courses.remove(course_id);
}

void EnrollmentRepository::drop_event(QString student_id, QUuid event_id) {
    events.remove(event_id);
}

QList<QUuid> EnrollmentRepository::get_student_courses(QString student_id) {
    return get_student_activities(student_id, ActivityType::CourseType);
}

QList<QUuid> EnrollmentRepository::get_student_events(QString student_id) {
    return get_student_activities(student_id, ActivityType::EventType);
}

QHash<QUuid, class Instructor> &EnrollmentRepository::get_instructors() {
    QFile file(getCurrentDir() + "/instructors.csv");
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());

    QTextStream stream(&file);
    QHash<QUuid, class Instructor> result;
    while(!stream.atEnd()) {
        QStringList row = stream.readLine().split(",");
        class Instructor instructor(QUuid(row[0]), row[1], row[2]);
        result.insert(instructor.get_id(), instructor);
    }

    file.close();
    instructors = result;
    return instructors;

}

class Instructor EnrollmentRepository::get_instructor(QUuid id) {
    qDebug() << "From Get Instructor" << instructors.size();
    if (instructors.isEmpty())
        get_instructors();

    qDebug() << "From Get Instructor" << instructors.size();
    if (!instructors.contains(id))
        throw std::runtime_error("Instructor not found");

    qDebug() << "From Get Instructor" << instructors.size();
    return instructors[id];
}


// This called only when the student dropping or registering for a course is not the current student
// For the current student, it is handled without opening any files
void EnrollmentRepository::enroll(QString student_id, QUuid activityId, ActivityType type) {
    QString filename = type == ActivityType::CourseType ? "students-courses.csv" : "students-events.csv";
    QFile file(getCurrentDir() + "/" + filename);

    if (!file.open(QIODevice::ReadWrite))
        throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());

    QTextStream stream(&file);
    QStringList newData;
    bool found = false;
    while(!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.split(",")[0] == student_id) {
            found = true;
            line += "," + activityId.toString();
        }
        newData.append(line);
    }

    if (!found)
        throw std::runtime_error("Student not found");

    // Write the new data
    file.resize(0);
    for (auto &line : newData)
        stream << line << "\n";

    file.close();
}


// This called only when the student dropping or registering for a course is not the current student
// For the current student, it is handled without opening any files
void EnrollmentRepository::drop(QString student_id, QUuid course_id, ActivityType type) {

    QString filename = type == ActivityType::CourseType ? "students-courses.csv" : "students-events.csv";
    QFile file(getCurrentDir() + "/" + filename);

    if (!file.open(QIODevice::ReadWrite))
        throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());

    QTextStream stream(&file);
    QStringList newData;
    bool found = false;
    while(!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.split(",")[0] == student_id) {
            found = true;
            QStringList activities = line.split(",");
            activities.removeAll(course_id.toString());
            line = activities.join(",");
        }
        newData.append(line);
    }

    if (!found)
        throw std::runtime_error("Student not found");

    // Write the new data
    file.resize(0);
    for (auto &line : newData)
        stream << line << "\n";

    file.close();

}

QList<QUuid> EnrollmentRepository::get_student_activities(QString student_id, ActivityType type) {

    qDebug() << "From Get" << courses.size() << events.size();
    QList<QUuid> result;
    if (type == ActivityType::CourseType) {
        for(auto &course : courses)
            result.append(course);
    } else {
        for(auto &event : events)
            result.append(event);
    }

    return result;


}

void EnrollmentRepository::load(QString student_id, ActivityType type) {
    QString filename = type == ActivityType::CourseType ? "students-courses.csv" : "students-events.csv";
    QFile file(getCurrentDir() + "/" + filename);

    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());

    QTextStream stream(&file);
    QStringList activities;
    while(!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.split(",")[0] == student_id)
            activities = line.split(",");
    }

    file.close();

    for (int i = 1; i < activities.size(); i++) {
        QUuid id = QUuid(activities[i]);
        if (type == ActivityType::CourseType)
            courses.insert(id);
        else
            events.insert(id);
    }

}

void EnrollmentRepository::store(QString student_id, ActivityType type) {
    QString filename = type == ActivityType::CourseType ? "students-courses.csv" : "students-events.csv";
    QFile file(getCurrentDir() + "/" + filename);

    if (!file.open(QIODevice::ReadWrite))
        throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());

    // Write the new data
    QTextStream stream(&file);
    QStringList newData;
    while(!stream.atEnd()) {
        QString line = stream.readLine();
        qDebug() << "From store of enrollment" << line;
        if (line.split(",")[0] == student_id) {
            line = student_id;
            if (type == ActivityType::CourseType) {
                for(auto &course : courses)
                    line += "," + course.toString();
            } else {
                for(auto &event : events)
                    line += "," + event.toString();
            }
        }
        newData.append(line);
    }

    // Write the new data
    file.resize(0);
    stream.setDevice(&file);
    for (auto &line : newData)
        stream << line << "\n";

    if (type == ActivityType::CourseType)
        courses.clear();
    else
        events.clear();

    file.close();
}
