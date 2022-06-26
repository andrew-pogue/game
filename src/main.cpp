#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <string>

#include "game.hh"

void must_init(bool test, const char *description) {
    if(test) return;
    printf("Failed to initialize %s!\n", description);
    printf("Main End\n");
    exit(1);
}

int main (int argc, char **argv) {
    must_init(al_init(), "Allegro");
    must_init(al_init_font_addon(), "font addon");
    must_init(al_init_ttf_addon(), "ttf addon");
    must_init(al_init_image_addon(), "image addon");
    must_init(al_init_primitives_addon(), "primitives addon");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    (void)argc;
    (void)argv;

    // std::string font_path = "assets/font/PressStart2P-Regular.ttf";
    // int font_size = 24;
    // for (auto i = 0; i < argc; i++) {
    //     switch (i) {
    //     case 1:
    //         font_path = argv[i];
    //         break;
    //     case 2:
    //         int i = atoi(argv[i]);
    //         if (i > 0) font_size = i;
    //         break;
    //     default:
    //         break;
    //     }
    // }

    Game game;
    game.play();

    // Game* game = nullptr;

    // game = new Game();
    
    // try {
    //     game = new Game(font_path, font_size);
    //     game->play();
    // }

    // catch(const char * error) {
    //     printf("%s\n", error);
    //     delete game;
    //     printf("Main End\n");
    //     return 1;
    // }

    // delete game;
    return 0;
}
