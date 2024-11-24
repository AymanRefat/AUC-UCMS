#ifndef EMAIL_H
#define EMAIL_H
#include <QString>
#include <QRegularExpression>

class Email
{
    static const QRegularExpression emailRegExp;
    QString email;
public:
    Email(QString);
    Email();
    QString get_email()const;
    void set_email(QString);
    bool operator==(Email);
    static bool is_valid_email (QString);

};

#endif // EMAIL_H
