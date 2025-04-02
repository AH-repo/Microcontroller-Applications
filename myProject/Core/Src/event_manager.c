#include "event_manager.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

// Maximum number of events handled by the event manager
#define MAX_NUMBER_OF_EVENTS 10

// Table of Event handles
static Event* events[MAX_NUMBER_OF_EVENTS];


void EVENT_MANAGER_Init(void) {
    memset(events, 0, sizeof(events));
}


bool EVENT_MANAGER_RegisterEvent(Event* event, OnEventHandler onEvent, void* context) {
    for (int i = 0; i < MAX_NUMBER_OF_EVENTS;  i++){
        if (events[i] == NULL) {
            events[i] = event;
            event->onEvent = onEvent;
            event->context = context;
            return true;
        };
    };
	return false;
}


void EVENT_MANAGER_UnregisterEvent(Event* event) {
    for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++){
        if(events[i] == event){
            events[i] = NULL;
        }
    }
}


bool EVENT_MANAGER_ScheduleEvent(Event* event, uint64_t time) {
    for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++){
        if(events[i] == event){
            event -> isScheduled = true;
            event -> scheduledTime = time;

            return true;
        }
    }
	return false;
}


void EVENT_MANAGER_Proc(uint64_t currentTime) {
    for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++){
        if (events[i] != NULL){
            if (events[i]->isScheduled == true && (events[i]->scheduledTime <= currentTime)){
            events[i]->isScheduled = false;
            events[i]->onEvent(events[i], events[i]->scheduledTime, events[i]->context);
            }
        }
    }
}

