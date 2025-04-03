#include <SDL2/SDL.h>
#include <stdio.h>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PI = 3.1415926535f;

void drawTriangle(SDL_Renderer *renderer, float angle) {
    SDL_Point points[4];
    float cx = WINDOW_WIDTH / 2.0f;
    float cy = WINDOW_HEIGHT / 2.0f;
    float size = 100.0f;

    for (int i = 0; i < 3; i++) {
        float theta = angle + (2 * PI * i / 3);
        points[i].x = static_cast<int>(cx + size * cos(theta));
        points[i].y = static_cast<int>(cy + size * sin(theta));
    }
    points[3] = points[0]; // Close the triangle

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLines(renderer, points, 4);
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Silverwing Sim", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, 
                                          WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;
    float angle = 0.0f;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawTriangle(renderer, angle);
        SDL_RenderPresent(renderer);

        angle += 0.02f; // Rotation speed
        SDL_Delay(16); // Roughly 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


// #include <SDL2/SDL.h>
// #include <stdio.h>
//
// int main(int arc, char **argv) {
//   SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Silverwing Sim",
//                            "Starting SSS", 0);
//   return 0;
// }
