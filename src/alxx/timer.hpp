#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>

// Wrapper for ALLEGRO_TIMER
class Timer {
public:

    Timer::Timer(double seconds) : timer_(nullptr) {
        timer_ = al_create_timer(seconds);
        if (!timer_) throw "Error: failed to create timer.";
    }

    Timer::~Timer() {
        al_destroy_timer(timer_);
    }

    void Timer::start() {
        al_start_timer(timer_);
    }

    void Timer::stop() {
        al_stop_timer(timer_);
    }

    void Timer::resume() {
        al_resume_timer(timer_);
    }

    operator ALLEGRO_TIMER*() {
        return timer_;
    }

    operator ALLEGRO_EVENT_SOURCE*() {
        return al_get_timer_event_source(timer_); 
    }

private:

    ALLEGRO_TIMER* timer_;

};