#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>

// Wrapper for ALLEGRO_EVENT_QUEUE
class EventQueue {
public:

    EventQueue() 
        : queue_(al_create_event_queue()) 
    {
        if (!queue_) throw "Error: Failed to create event queue.";
    }

    ~EventQueue() {
        al_destroy_event_queue(queue_);
    }

    void add_source(ALLEGRO_EVENT_SOURCE *source) {
        al_register_event_source(queue_, source);
    }

    bool is_empty() {
        return al_is_event_queue_empty(queue_);
    }

    bool has_source(ALLEGRO_EVENT_SOURCE *source) {
        return al_is_event_source_registered(queue_, source);
    }

    void wait_for_event(ALLEGRO_EVENT *event) {
        al_wait_for_event(queue_, event);
    }

    operator ALLEGRO_EVENT_QUEUE* () {
        return queue_;
    }

private:

    ALLEGRO_EVENT_QUEUE* queue_;

};