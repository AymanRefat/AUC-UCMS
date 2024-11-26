#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QDialog>


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
    UserID,Firstname,Lastname
};

enum StudentDataRow {
    Gpa = UserInfoDataRow::Lastname + 1,
    StudentClassStanding
};

enum AdminDataRow {
    Role = UserInfoDataRow::Lastname + 1,
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

// week days
const QStringList days = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

const QStringList class_standings = {
    "Freshman", "Sophomore", "Junior", "Senior"
};

void load_logout_button(QDialog* parent);
// Functions


#endif // UTILS_H
