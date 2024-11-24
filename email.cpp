#include "email.h"
#include "utils.cpp"
#include <QString>

const QRegularExpression Email::emailRegExp = QRegularExpression(R"((\w+)(\.{0,1}(\w+))*@(\w+)(\.\w+)+)");

Email::Email() {
    email="";
}

Email::Email(QString email){
    set_email(email);
}
QString Email::get_email() const {
    return email ;
}
void Email::set_email(QString newEmail){
    // if ( !is_valid_email(newEmail)){
        // throw std::invalid_argument("Invalid email");
    // }
    email = newEmail;
}


bool Email::operator==(Email emailToCompare){
    return email == emailToCompare.get_email();
}

bool Email::is_valid_email(QString email){
    return emailRegExp.match(email).hasMatch();
}

