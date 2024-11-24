#include "eventrepository.h"
#include "event.h"

EventRepository::EventRepository() : ActivityRepository(ActivityType::EventType, "events.csv") {
    // Testing CourseRepository
    load();
    QList<Activity*> activities = get_all();
    // print all
    for (auto &activity : activities)
        qDebug() << activity->get_title();

    // remove(activities[0]);
    add(new class Event("Event 1", "Description 1", "Location 1", 10, QUuid::createUuid(), QUuid::createUuid(), QDate::currentDate(), QDate::currentDate(), QTime::currentTime(), QTime::currentTime()));
    activities[1]->set_title("This is my title updated");
    update(activities[1]);
    store();
}
