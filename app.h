#ifndef APP_H
#define APP_H

#include "courserepository.h"
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

private:
    CourseRepository * course_repository;
    EventRepository * event_repository;

public:
    App();
    ~App();
    CourseManager * course_manager;
    EventManager * event_manager;


};

#endif // APP_H