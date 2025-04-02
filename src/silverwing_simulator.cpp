#include <SDL2/SDL.h>

int main(int arc, char ** argv) {
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize!\n");
    } else {
        SDL_CreateWindow(
            "SDL2 Demo",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_SHOWN
        );

        SDL_Delay(2000);
    }

    return 0;
}
