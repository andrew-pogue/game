#pragma once
#include <allegro5/allegro.h>
#include <functional>
#include <vector>

class EventHandler {
public:

    EventHandler() 
        : functions_(ALLEGRO_EVENT_DISPLAY_DISCONNECTED+1)
    {
    }

    EventHandler(int max_event_id) 
        : functions_(max_event_id)
    {
    }

    auto& on_event(int event_type) {
        if (debug) printf("EventHandler::on_event(%i)\n", event_type);
        if ((size_t)event_type >= functions_.size()) {
            functions_.resize(event_type+1);
        }
        return functions_.at(event_type);
    }

    void update(ALLEGRO_EVENT event) {
        if (debug) printf("EventHandler::update({%i})\n", event.type);
        if (on_event(event.type)) on_event(event.type)(event);
    }

    static inline bool debug = false;

private:

    std::vector<std::function<void(ALLEGRO_EVENT)>> functions_;

};