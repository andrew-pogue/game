#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>

// Wrapper for ALLEGRO_EVENT_QUEUE
class EventQueue {
public:

    EventQueue();
    ~EventQueue();

    void register_source(ALLEGRO_EVENT_SOURCE* source);

    bool is_empty();
    bool is_source_registered(ALLEGRO_EVENT_SOURCE* source);

    void wait_for_event(ALLEGRO_EVENT* event);

    // operator ALLEGRO_EVENT_QUEUE* ();

private:

    ALLEGRO_EVENT_QUEUE* queue_;

};