#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QStringList>
#include <QList>


// Enums
enum ClassStanding {
    Freshman ,Sophomore  , Junior ,  Senior
};

enum UserType {
    Admin , Student
};

enum ActivityType {
    CourseType, EventType
};


enum ActivityDataRow {
    Id, Title , Description, Capacity, Location, StartDate, EndDate, StartTime, EndTime
};

enum CourseDataRow {
    InstructorId = ActivityDataRow::EndTime + 1,
    Days
};

enum EventDataRow {
    SpeakerId = ActivityDataRow::EndTime + 1
};

enum UserAuthDataRow {
    Username, Password, Email, Phone, UserId, Type
};

enum UserInfoDataRow {
    UserID,Firstname,Lastname,Address
};

enum StudentDataRow {
    Gpa = UserInfoDataRow::Address + 1,
    StudentClassStanding
};

enum AdminDataRow {
    Role = UserInfoDataRow::Address + 1,
    Salary
};

enum Day {
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
};

enum AdminRole {
    Instructor, TA
};

QStringList parseCsvLine(const QString &line);
QString getCurrentDir();

// Functions


#endif // UTILS_H
