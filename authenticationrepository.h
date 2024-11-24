#ifndef AUTHENTICATIONREPOSITORY_H
#define AUTHENTICATIONREPOSITORY_H

#include "qdir.h"
#include "user.h"
#include "utils.h"
#include <QString>
// TODO : add this logic to the UsersManager class
// TODO : instead Create interface load , store for reading and writing in the file
class AuthenticationRepository
{
private:
    User* current_user = nullptr;
public:
    AuthenticationRepository();

    // Logic
    User* login(QString username, QString password);
    void logout();
    void signup(User* newUser);

    // Getters
    User* get_current_user();

private:
    QStringList get_user_info(QUuid id, UserType type);
    void verifyCredentials(User *user, QFile& file);
};

#endif // AUTHENTICATIONREPOSITORY_H
