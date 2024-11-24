#ifndef ACTIVITYREPOSITORY_H
#define ACTIVITYREPOSITORY_H

#include "activity.h"
#include "utils.h"

// Handles data mangeament for courses and events
// For now it is abstract. We might get rid of the courseRepository and eventRepository classes and use this class directly
class ActivityRepository
{
protected:
    // Type of activity (Course/Event)
    ActivityType type;

    // Filename to fetch/store data
    QString filename;

    // Container to store data
    QHash<QUuid, Activity*> container;

public:

    // Preconditions: type is a valid ActivityType, filename is a valid QString
    // Postconditions: ActivityRepository object is created member variables are initialized
    ActivityRepository(ActivityType type, QString filename);

    // Preconditions: none
    // Postconditions: ActivityRepository object is destroyed
    virtual ~ActivityRepository() = 0; // Made virtual to make the class abstract

    // Data managers

    // Preconditions: none
    // Postconditions: Data is loaded from the file and stored in the container
    void load();

    // Preconditions: none
    // Postconditions: Data is stored in the file from the container
    void store();

    // Preconditions: activity is a valid Activity object
    // Postconditions: activity is added to the container
    void add(Activity* activity);

    // Preconditions: activity is a valid Activity object
    // Postconditions: activity is removed from the container
    void remove(Activity* activity);

    // Preconditions: id is a valid QUuid
    // Postconditions: activity is removed from the container
    void remove(QUuid id);

    // Preconditions: activity is a valid Activity object
    // Postconditions: activity is updated in the container
    void update(Activity* activity);

    // Preconditions: id is a valid QUuid
    // Postconditions: activity is returned from the container if it exists. Error is thrown otherwise
    Activity* get(QUuid id);

    // Preconditions: ids is a valid QList of QUuid
    // Postconditions: activities are returned from the container if they exist. Error is thrown otherwise
    QList<Activity*> get(QList<QUuid> ids);

    // Preconditions: none
    // Postconditions: all the activities are returned from the container
    QList<Activity*> get_all();
};

#endif // ACTIVITYREPOSITORY_H
