#include "authenticationrepository.h"
#include "admin.h"
#include "qdir.h"
#include "student.h"
#include "utils.h"
#include <QCryptographicHash>
#include <QFile>
#include <QUuid>

AuthenticationRepository::AuthenticationRepository() {}

void AuthenticationRepository::login(QString username, QString password) {
    if (current_user != nullptr)
        throw std::runtime_error("User already logged in");

    QFile file(getCurrentDir() + "/users-auth.csv");
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());

    QTextStream in(&file);
    in.readLine();
    while(!in.atEnd()) {
        QStringList row = parseCsvLine(in.readLine());

        // hash password
        QString hashed_password = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());
        if (row[UserAuthDataRow::Username] == username && row[UserAuthDataRow::Password] == hashed_password) {

            qDebug() << username << " " << row[UserAuthDataRow::Username] << " " << row[UserAuthDataRow::UserId];
            QStringList userInfo = get_user_info(QUuid(row[UserAuthDataRow::UserId]), UserType(row[UserAuthDataRow::Type].toInt()));

            if (row[UserAuthDataRow::Type].toInt() == UserType::Admin) {
                current_user = new class Admin(
                    userInfo[UserInfoDataRow::UserID], username, password,
                    userInfo[UserInfoDataRow::Firstname], userInfo[UserInfoDataRow::Lastname],
                    row[UserAuthDataRow::Email],
                    row[UserAuthDataRow::Phone], AdminRole(row[AdminDataRow::Role].toInt()),
                    userInfo[AdminDataRow::Salary].toDouble()
                    );
            } else {
                current_user = new class Student(
                    userInfo[UserInfoDataRow::UserID], username, password,
                    userInfo[UserInfoDataRow::Firstname], userInfo[UserInfoDataRow::Lastname],
                    row[UserAuthDataRow::Email],
                    row[UserAuthDataRow::Phone], userInfo[StudentDataRow::Gpa].toDouble(),
                    ClassStanding(userInfo[StudentDataRow::StudentClassStanding].toInt())
                    );
            }

            return;
        }

    }

    throw std::runtime_error("Invalid username or password");

}

void AuthenticationRepository::signup(User* newUser) {
    QFile file(getCurrentDir() + "/users-auth.csv");

    // Verifying user credentials
    verifyCredentials(newUser, file);

    // Writing Authentication data
    if (!file.open(QIODevice::Append))
        throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());
    QTextStream out(&file);
    // Hash passowrd
    QString hashed_password = QString(QCryptographicHash::hash(newUser->get_password().toUtf8(), QCryptographicHash::Md5).toHex());

    // Get user type
    UserType type;
    if (dynamic_cast<class Student*>(newUser) != nullptr)
        type = UserType::Student;
    else
        type = UserType::Admin;

    out << newUser->get_username() << "," << hashed_password << "," << newUser->get_email() << "," << newUser->get_phone_number() << "," << newUser->get_id() << "," << type << "\n";
    file.close();


    // Writing User Info
    file.setFileName(getCurrentDir() + (type == UserType::Admin ? "/admins-info.csv" : "/students-info.csv"));
    if (!file.open(QIODevice::Append))
        throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());

    out.setDevice(&file);

    if (type == UserType::Admin) {
        class Admin* admin = dynamic_cast<class Admin*>(newUser);
        out << admin->get_id() << "," << admin->get_firstname() << "," << admin->get_lastname() << "," << admin->get_salary() << "," << admin->get_role() << "\n";
    } else {
        class Student* student = dynamic_cast<class Student*>(newUser);
        out << student->get_id() << "," << student->get_firstname() << "," << student->get_lastname() << "," << student->get_gpa() << "," << student->get_class_standing() << "\n";
    }

    file.close();

    // Adding Id to students-courses.csv and students-events.csv
    if (type == UserType::Student) {
        file.setFileName(getCurrentDir() + "/students-courses.csv");
        if (!file.open(QIODevice::Append))
            throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());
        out.setDevice(&file);
        out << newUser->get_id() << "\n";
        file.close();

        file.setFileName(getCurrentDir() + "/students-events.csv");
        if (!file.open(QIODevice::Append))
            throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());
        out.setDevice(&file);
        out << newUser->get_id() << "\n";
        file.close();
    }

    file.close();

}

void AuthenticationRepository::logout() {
    if (current_user == nullptr)
        throw std::runtime_error("No user logged in");

    delete current_user;
    current_user = nullptr;
}

User* AuthenticationRepository::get_current_user() {
    if (current_user == nullptr)
        throw std::runtime_error("No user logged in");

    return current_user;
}

QStringList AuthenticationRepository::get_user_info(QUuid id, UserType type) {
    QString path = type == UserType::Admin ? getCurrentDir() + "/admins-info.csv" : getCurrentDir() + "/students-info.csv";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());

    QTextStream in(&file);
    in.readLine();

    while(!in.atEnd()) {
        QStringList row = parseCsvLine(in.readLine());
        if (QUuid(row[UserInfoDataRow::UserID]) == id) {
            return row;
        }
    }

    throw std::runtime_error("User not found");

}

void AuthenticationRepository::verifyCredentials(User *user, QFile &file) {
    if (!file.open(QIODevice::ReadOnly))
      throw std::runtime_error(("Could not open file: " + file.fileName() + ", Error: " + file.errorString()).toStdString());

    QTextStream in(&file);
    in.readLine();

    while(!in.atEnd()) {
       QStringList row = parseCsvLine(in.readLine());
        if (row[UserAuthDataRow::Username] == user->get_username()) {
           file.close();
            throw std::runtime_error("Username already exists");
        }
        if (row[UserAuthDataRow::Email] == user->get_email()) {
            file.close();
            throw std::runtime_error("Email already exists");
        }
        if (row[UserAuthDataRow::Phone] == user->get_phone_number()) {
            file.close();
            throw std::runtime_error("Phone number already exists");
        }
        if (row[UserAuthDataRow::UserId] == user->get_id()) {
            file.close();
            throw std::runtime_error("User id already exists");
        }
    }

    file.close();


}
