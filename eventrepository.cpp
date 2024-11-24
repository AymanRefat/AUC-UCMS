#include "eventrepository.h"
#include "event.h"

EventRepository::EventRepository() : ActivityRepository(ActivityType::EventType, "events.csv") {
}
