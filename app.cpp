#include "app.h"

App::App() {
    // Load data when the app starts
    course_repository = new  CourseRepository();
    course_repository->load();
    event_repository = new EventRepository();
    event_repository->load();
    event_manager =  new EventManager(*this);
    course_manager = new CourseManager(*this);
}
App::CourseManager::CourseManager(App &app) : app(app) {}
App::EventManager::EventManager(App &app) : app(app ) {}

App::~App() {
    // Save data before closing the app
    course_repository->store();
    event_repository->store();
    delete course_repository;
    delete event_repository;
    delete course_manager;
    delete event_manager;
}

// CRUD operations for events
void App::EventManager::create(Event* event){
    app.event_repository->add(event);
}

void App::EventManager::update(Event* event){
    app.event_repository->update(event);
}

void App::EventManager::remove(Event* event){
    app.event_repository->remove(event);
}

Event* App::EventManager::get(QUuid id){
    return dynamic_cast<Event*>(app.event_repository->get(id));
}

QList<Event*> App::EventManager::get_all(){
    QList<Event*> result;
    for (auto event : app.event_repository->get_all()){
        auto* e = dynamic_cast<Event*>(event);
        if (e != nullptr){
            result.append(e);
        }
    }
    return result;
}

// Crud Operations for courses

void App::CourseManager::create(Course* course){
    app.course_repository->add(course);
}

void App::CourseManager::update(Course* course){
    app.course_repository->update(course);
}

void App::CourseManager::remove(Course* course){
    app.course_repository->remove(course);
}

Course* App::CourseManager::get(QUuid id ) {
    return dynamic_cast<Course*>(app.course_repository->get(id));
}

QList<Course*> App::CourseManager::get_all() {
    QList<Course*> result ;
    for ( auto course : app.event_repository->get_all()){
        auto* c = dynamic_cast<Course*>(course);
        if ( c != nullptr){
            result.append(c);
        }
    }
    return result ;
}



