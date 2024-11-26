#include "app.h"
#include "admin_page.h"
#include "course.h"
#include "dashboard.h"
#include "event.h"
#include "admin.h"
#include "mainwindow.h"
#include "student.h"
#include "utils.h"
#include <QMessageBox>
#include <QRegularExpression>
App::App() {
    // Load data when the app starts
    course_repository = new  CourseRepository();
    course_repository->load();
    event_repository = new EventRepository();
    event_repository->load();
    auth_repository = new AuthenticationRepository();
    enrollment_repository = new EnrollmentRepository();
    event_manager =  new EventManager(*this);
    course_manager = new CourseManager(*this);
    auth_manager = new AuthManager(*this);
    enrollment_manager = new EnrollmentManager(*this);

    current_window = nullptr;
}
App::CourseManager::CourseManager(App &app) : app(app) {}
App::EventManager::EventManager(App &app) : app(app ) {}
App::AuthManager::AuthManager(App &app) : app(app) {}
App::EnrollmentManager::EnrollmentManager(App &app) : app(app) {}

App::~App() {
    // Save data before closing the app
    course_repository->store();
    event_repository->store();
    delete course_repository;
    delete event_repository;
    delete auth_repository;
    delete course_manager;
    delete event_manager;
    delete auth_manager;
    delete enrollment_manager;
    delete current_window;

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
    QList<Activity*> activities = app.course_repository->get_all();
    QList<Course*> result ;
    for (auto activity : activities){
        auto* c = dynamic_cast<Course*>(activity);
        if ( c != nullptr){
            result.append(c);
        }
    }
    return result ;
}

// AuthManager

void App::AuthManager::login(QString username, QString password){
    try {
        if (username.isEmpty() || password.isEmpty()){
            QMessageBox::warning(app.current_window, "Error", "All fields are required");
            return;
        }

        app.auth_repository->login(username, password);
        app.enrollment_repository->load(app.auth_repository->get_current_user()->get_id());

        app.current_window->hide();
        if (app.current_window != nullptr)
            delete app.current_window;

        if (app.auth_repository->get_current_user()->get_type() == Student)
            app.current_window = new Dashboard();
        else
            app.current_window = new Admin_page();
        app.current_window->show();

    } catch (std::exception &e){
        QMessageBox::warning(app.current_window, "Error", e.what());
    }
}

void App::AuthManager::signup(QString id, QString username, QString password, QString firstname, QString lastname, QString email, QString phone, QString type){

    if (id.isEmpty() || username.isEmpty() || password.isEmpty() || firstname.isEmpty() || lastname.isEmpty() || email.isEmpty() || phone.isEmpty()){
        QMessageBox::warning(app.current_window, "Error", "All fields are required");
        return;
    }

    if (!Email::is_valid_email(email)) {
        QMessageBox::warning(app.current_window, "Error", "Invalid email address");
        return;
    }

    // check if phone has anything other than numbers
    if (!phone.contains(QRegularExpression(("[0-9]+")))) {
        QMessageBox::warning(app.current_window, "Error", "Invalid phone number");
        return;
    }

    // check if id has anything other than numbers
    if (id.length() != 8 || !id.contains(QRegularExpression("^[0-9]*$"))) {
        QMessageBox::warning(app.current_window, "Error", "Invalid id");
        return;
    }

    try {
        if (type == "Student") {
            // Create a new student
            app.auth_repository->signup(new class Student(
                                            id, username, password, firstname, lastname, email, phone, 0.0, ClassStanding::Freshman
                                            ), type);
        } else {
            // Create a new admin
            app.auth_repository->signup(new class Admin(
                                            id, username, password, firstname, lastname, email, phone, AdminRole::Instructor, 3000
                                            ), type);
        }


        if (app.current_window != nullptr) {
            app.current_window->hide();
            delete app.current_window;
        }

        if (type == "Student") {
            app.current_window = new Dashboard();
        } else {
            app.current_window = new Admin_page();
        }
        app.current_window->show();


    } catch(std::exception &e){
        // Notify user
        QMessageBox::warning(app.current_window, "Error", e.what());
    }
}

void App::AuthManager::logout(){

    try {
        app.current_window->close();
        app.course_repository->store();
        app.event_repository->store();
        app.enrollment_repository->store(app.auth_repository->get_current_user()->get_id());
        app.auth_repository->logout();

        if (app.current_window != nullptr)
            delete app.current_window;

        app.current_window = new MainWindow();
        app.current_window->show();
    } catch (std::exception &e){
        QMessageBox::warning(app.current_window, "Error", e.what());
        return;
    }

}

User *App::AuthManager::get_current_user(){
    return app.auth_repository->get_current_user();
}

// EnrollmentManager
QList<Course*> App::EnrollmentManager::get_student_courses(QString student_id){
    QList<QUuid> courses_ids = app.enrollment_repository->get_student_courses(student_id);
    QList<Course*> courses;
    for (auto id : courses_ids){
        try {
            app.course_repository->get(id);
        } catch (std::exception &e){
            continue;
        }
        Course* course = dynamic_cast<Course*>(app.course_repository->get(id));
        if (course != nullptr){
            courses.append(course);
        }
    }
    return courses;
}

QList<Event*> App::EnrollmentManager::get_student_events(QString student_id){
    QList<QUuid> events_ids = app.enrollment_repository->get_student_events(student_id);
    QList<Event*> events;
    for (auto id : events_ids){
        try {
            app.event_repository->get(id);
        } catch (std::exception &e){
            continue;
        }
        Event* event = dynamic_cast<Event*>(app.event_repository->get(id));
        if (event != nullptr){
            events.append(event);
        }
    }
    return events;
}

QList<class Instructor> App::EnrollmentManager::get_instructors(){
    QHash<QUuid, class Instructor> instructors = app.enrollment_repository->get_instructors();
    QList<class Instructor> result;
    for (auto &instructor : instructors){
        result.append(instructor);
    }
    return result;
}

class Instructor App::EnrollmentManager::get_instructor(QUuid id){
    return app.enrollment_repository->get_instructor(id);
}

class Instructor App::EnrollmentManager::get_instructor(QString instructor_name){
    return app.enrollment_repository->get_instructor(instructor_name);
}

void App::EnrollmentManager::enroll_in_course(QString student_id, QUuid course_id){
    try {
        app.enrollment_repository->enroll_in_course(student_id, course_id);
        QMessageBox::information(app.current_window, "Success", "Course registered successfully!");
    } catch (std::exception &e){
        QMessageBox::warning(app.current_window, "Error", e.what());
    }
}

void App::EnrollmentManager::enroll_in_event(QString student_id, QUuid event_id){
    try {
        app.enrollment_repository->enroll_in_event(student_id, event_id);
        QMessageBox::information(app.current_window, "Success", "Event registered successfully!");
    } catch (std::exception &e){
        QMessageBox::warning(app.current_window, "Error", e.what());
    }
}

void App::EnrollmentManager::drop_course(QString student_id, QUuid course_id){
    app.enrollment_repository->drop_course(student_id, course_id);
    app.current_window->hide();
    if (app.current_window != nullptr){
        delete app.current_window;
    }
    app.current_window = new Dashboard(nullptr);
    app.current_window->show();
}

void App::EnrollmentManager::drop_event(QString student_id, QUuid event_id){
    app.enrollment_repository->drop_event(student_id, event_id);
    app.current_window->hide();
    if (app.current_window != nullptr){
        delete app.current_window;
    }
    app.current_window = new Dashboard(nullptr);
    app.current_window->show();
}

void App::set_current_window(QWidget *window){
    current_window = window;
}

QWidget *App::get_current_window(){
    return current_window;
}
