#pragma once

#include <allegro5/allegro.h>
#include <bitset>
#include <iostream>

#include "alxx/display.hpp"
#include "alxx/event_queue.hpp"
#include "alxx/timer.hpp"
#include "constants.hh"
#include "entity.hh"
#include "glyh.hh"
#include "io/keyboard.hh"
#include "io/mouse.hh"
#include "scene/scene.hh"

const signature_t
    COLLIDE = 1,
    MOVE = 2;
const float SPEED = 5.0f;

class Game {
public:

    Game() 
        : status_(0)
        , display_(WINDOW_WIDTH, WINDOW_HEIGHT, "Game")
        , event_queue_()
        , frame_timer_(1.0/30.0)
        , keyboard_()
        , mouse_(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0)
        , scene_({0,0,0})
        , player_(nullptr)
        , x_((float)WINDOW_WIDTH/2.0f)
        , y_((float)WINDOW_HEIGHT/2.0f)
    {
        event_queue_.register_source(al_get_keyboard_event_source());
        event_queue_.register_source(al_get_mouse_event_source());
        event_queue_.register_source(display_);
        event_queue_.register_source(frame_timer_);
        
        display_[ALLEGRO_EVENT_DISPLAY_CLOSE] = [&](unsigned){
            status_[PLAY] = false;
        };

        keyboard_[ALLEGRO_KEY_ESCAPE] = [&](unsigned){
            status_[PLAY] = false;
        };

        keyboard_[ALLEGRO_KEY_UP] = [&](unsigned){
            y_ -= SPEED;
        };

        keyboard_[ALLEGRO_KEY_DOWN] = [&](unsigned){
            y_ += SPEED;
        };

        keyboard_[ALLEGRO_KEY_LEFT] = [&](unsigned){
            x_ -= SPEED;
        };

        keyboard_[ALLEGRO_KEY_RIGHT] = [&](unsigned){
            x_ += SPEED;
        };
    }
    
    ~Game() {
        printf("~Game()\n");
    }
    
    void play() {
        printf("play()\n");
        status_[PLAY] = true;
        ALLEGRO_EVENT event;

        player_ = new Entity("player", 0, MOVE | COLLIDE);
        Font font("assets/font/PressStart2P-Regular.ttf", 36);
        printf("Font=%s\n", font.name());
        *player_ += new Glyph('@', font, "white");

        frame_timer_.start();
        while(status_[PLAY]) {
            event_queue_.wait_for_event(&event);

            display_.update(event);
            keyboard_.update(event);
            mouse_.update(event);

            player_->update();
            this->update();
            
            if (event.type == ALLEGRO_EVENT_TIMER) {
                status_[RENDER] = true;
            }

            if (status_[RENDER] && event_queue_.is_empty()) {

                status_[RENDER] = false;
                al_clear_to_color(al_map_rgb(0,0,0));
                player_->render(x_, y_);
                al_flip_display();

                // this->render();
            }
        }
    
        delete player_;
        printf("Exit\n");
    }

protected:

    const unsigned
        PLAY = 0,
        RENDER = 1;

    void update() {
        for (auto command : display_.get_commands()) {
            command.run(0);
        }

        for (auto command : keyboard_.get_commands()) {
            command.run(0);
        }

        for (auto command : mouse_.get_commands()) {
            command.run(0);
        }
    }

    void render() {
        status_[RENDER] = false;
        al_clear_to_color(al_map_rgb(0,0,0));
        al_flip_display();
    }

    std::bitset<8> status_;
    Display display_;
    EventQueue event_queue_;
    Timer frame_timer_;
    Keyboard keyboard_;
    Mouse mouse_;
    Scene scene_;
    Entity *player_;
    float x_, y_;

};