#pragma once

#include <allegro5/allegro.h>
#include <bitset>
#include <queue>
#include <utility>
#include <vector>

#include "display.hh"
#include "event_queue.hh"
#include "timer.hh"
#include "camera.hh"
#include "constants.hh"
#include "entity.hh"
#include "manager.hh"
#include "event_handler.hh"
#include "glyh.hh"
#include "grid.hh"
#include "input_device.hh"
#include "text.hh"
#include "level.hh"

class Game {
public:

    Game(cstr name)
        : status_(0)
        , display_(WINDOW_WIDTH, WINDOW_HEIGHT, name)
        , camera_({0,0,0}, WINDOW_WIDTH, WINDOW_HEIGHT, TILE_SIZE)
        , frame_timer_(1.0/30.0)
        , event_queue_()
        , event_handler_()
        , keyboard_()
        , mouse_()
        , level_({0,0,0})
        , entity_manager_()
        , player_(0)
    {
        if (debug) printf("Game::Game()\n");
        Font font("assets/font/PressStart2P-Regular.ttf", 36);
        printf("Font=%s\n", font.name());

        size_t text = entity_manager_.create();
        entity_manager_.graphic<Text>(text, "Hello World!", font, "green", ALLEGRO_ALIGN_CENTER);
        level_.add(text, entity_manager_.flags(text), {4,3,0});

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                size_t tile = entity_manager_.create();
                entity_manager_.graphic<Glyph>(tile, '#', font, "white", ALLEGRO_ALIGN_CENTER);
                level_.add(tile, 0, {i,j,0});
            }
        }

        player_ = entity_manager_.create();
        entity_manager_.graphic<Glyph>(player_, '@', font, "red", ALLEGRO_ALIGN_CENTER);
        level_.add(player_, entity_manager_.flags(player_), {0,0,0});
        
        event_queue_.add_source(al_get_keyboard_event_source());
        event_queue_.add_source(al_get_mouse_event_source());
        event_queue_.add_source(display_);
        event_queue_.add_source(frame_timer_);

        event_handler_.on_event(ALLEGRO_EVENT_DISPLAY_RESIZE) =
            [&] (ALLEGRO_EVENT event) {
                (void)event;
                camera_.width((float)display_.width());
                camera_.height((float)display_.height());
            };
        event_handler_.on_event(ALLEGRO_EVENT_DISPLAY_CLOSE) =
            [&] (ALLEGRO_EVENT event) {
                (void)event;
                status_[PLAY] = false;
            };
        event_handler_.on_event(ALLEGRO_EVENT_KEY_DOWN) =
            [&] (ALLEGRO_EVENT event) {
                keyboard_.set_key_pressed(event.keyboard.keycode);
            };
        event_handler_.on_event(ALLEGRO_EVENT_KEY_UP) =
            [&] (ALLEGRO_EVENT event) {
                keyboard_.set_key_released(event.keyboard.keycode);
            };
        event_handler_.on_event(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) =
            [&] (ALLEGRO_EVENT event) {
                mouse_.set_key_pressed(event.mouse.button);
            };
        event_handler_.on_event(ALLEGRO_EVENT_MOUSE_BUTTON_UP) =
            [&] (ALLEGRO_EVENT event) {
                mouse_.set_key_released(event.mouse.button);
            };

        // ALLEGRO_EVENT_MOUSE_AXES -> update position of cursor
        // ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY -> enable cursor
        // ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY -> disable cursor

        keyboard_.on_input(ALLEGRO_KEY_ESCAPE) = 
            [&] (size_t id) {
                (void)id;
                status_[PLAY] = false;
            };
        keyboard_.on_input(ALLEGRO_KEY_UP) =
            [&] (size_t id) {
                auto coord = level_.coord_of(id);
                if (!coord) return;
                coord->y += 1;
                if (!level_.is_valid(*coord)) return;
                level_.remove(id);
                level_.add(player_, entity_manager_.flags(player_), *coord);
            };
        keyboard_.on_input(ALLEGRO_KEY_DOWN) =
            [&] (size_t id) {
                auto coord = level_.coord_of(id);
                if (!coord) return;
                coord->y -= 1;
                if (!level_.is_valid(*coord)) return;
                level_.remove(id);
                level_.add(player_, entity_manager_.flags(player_), *coord);
            };
        keyboard_.on_input(ALLEGRO_KEY_RIGHT) =
            [&] (size_t id) {
                auto coord = level_.coord_of(id);
                if (!coord) return;
                coord->x += 1;
                if (!level_.is_valid(*coord)) return;
                level_.remove(id);
                level_.add(player_, entity_manager_.flags(player_), *coord);
            };
        keyboard_.on_input(ALLEGRO_KEY_LEFT) =
            [&] (size_t id) {
                auto coord = level_.coord_of(id);
                if (!coord) return;
                coord->x -= 1;
                if (!level_.is_valid(*coord)) return;
                level_.remove(id);
                level_.add(player_, entity_manager_.flags(player_), *coord);
            };
    }

    ~Game() {
        if (debug) printf("Game::~Game()\n");
    }

    void play() {
        if (debug) printf("Game::play()\n");
        status_[PLAY] = true;
        
        ALLEGRO_EVENT event;

        frame_timer_.start();
        while(status_[PLAY]) {
            event_queue_.wait_for_event(&event);
            event_handler_.update(event);
            
            if (event.type == ALLEGRO_EVENT_TIMER) {
                status_[RENDER] = true;
                keyboard_.progress(player_);
                mouse_.progress(player_);
                
                auto coord = level_.coord_of(player_);
                if (coord) camera_.coord(*coord);
            }

            if (status_[RENDER] && event_queue_.is_empty()) {
                al_clear_to_color(al_map_rgb(0,0,0));
                
                for (auto coord : camera_.range()) {
                    if (!level_.is_valid(coord)) continue;
                    for (auto id : level_[coord].residents()) {
                        entity_manager_.draw(id, camera_.translate(coord));
                    }
                }

                // so that the player is drawn over other graphics:
                auto coord = level_.coord_of(player_);
                if (coord) entity_manager_.draw(player_, camera_.translate(*coord));
                
                al_flip_display();
                status_[RENDER] = false;
            }
        }
    }

    static inline bool debug = false;

private:

    const unsigned
        PLAY = 0,
        RENDER = 1;
    std::bitset<8> status_;
    
    Display display_;
    Camera camera_;
    Timer frame_timer_;
    
    EventQueue event_queue_;
    EventHandler event_handler_;
    
    Keyboard keyboard_;
    Mouse mouse_;
    
    Level<10,10,1> level_;
    Manager entity_manager_;
    size_t player_;

};