#ifndef APP_H
#define APP_H

#include "authenticationrepository.h"
#include "courserepository.h"
#include "enrollmentrepository.h"
#include "eventrepository.h"
#include "course.h"
#include "event.h"
#include <QString>
#include <QDate>
#include <QTime>
#include <QUuid>
#include <QSet>
// TODO : Create base Manager<Model>
class App
{
    // Crud operations for courses
    class CourseManager
    {
    public:
        App& app;
        explicit CourseManager(App& app); // Constructor
        void create(  Course* );
        void update(  Course* );
        void remove(  Course* );
        Course* get( QUuid );
        QList<Course*> get_all();
    };
    class EventManager
    {
        App& app;
    public :
        explicit EventManager(App& app); // Constructor
        void create(  Event* );
        void update( Event* );
        void remove( Event* );
        Event* get( QUuid );
        QList<Event*> get_all();

    };
    class AuthManager
    {
        App& app;
    public:
        explicit AuthManager(App& app); // Constructor
        void login(QString, QString);
        void signup(QString id, QString username, QString password, QString firstname, QString lastname, QString email, QString phone, QString type);
        void logout();
        User* get_current_user();
    };
    class EnrollmentManager
    {
        App& app;
    public:
        explicit EnrollmentManager(App& app); // Constructor
        void enroll_in_course(QString student_id, QUuid course_id);
        void enroll_in_event(QString student_id, QUuid event_id);
        void drop_course(QString student_id, QUuid course_id);
        void drop_event(QString student_id, QUuid event_id);
        QList<Course*> get_student_courses(QString student_id);
        QList<Event*> get_student_events(QString student_id);
        QList<class Instructor> get_instructors();
        class Instructor get_instructor(QUuid id);
        class Instructor get_instructor(QString instructor_name);
    };

private:
    CourseRepository * course_repository;
    EventRepository * event_repository;
    AuthenticationRepository * auth_repository;
    EnrollmentRepository * enrollment_repository;
    QWidget *current_window;

public:
    App();
    ~App();
    CourseManager * course_manager;
    EventManager * event_manager;
    AuthManager * auth_manager;
    EnrollmentManager * enrollment_manager;

    void set_current_window(QWidget *window);
    QWidget *get_current_window();
    void load_logout_button();


};

#endif // APP_H
