#include "./constants.h"
#include <SDL2/SDL.h>
// #include <SDL2/SDL_events.h>
// #include <SDL2/SDL_render.h>
// #include <SDL2/SDL_video.h>
#include <stdio.h>

int game_is_running = FALSE;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int initialise_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initalising SDL.\n");
    return FALSE;
  }

  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
  if (!window) {
    fprintf(stderr, "Error creating SDL Window.\n");
    return FALSE;
  }
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    fprintf(stderr, "Error creating SDL renderer.\n");
    return FALSE;
  }
  return TRUE;
}

void process_input() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      game_is_running = FALSE;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        game_is_running = FALSE;
      }
      break;
    }
  }
}

void setup() {
  // TODO:
}

void update() {
  // TODO:
}

void render() {
  // TODO:
}

void destroy_window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main() {
  game_is_running = initialise_window();

  setup();

  while (game_is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();

  return TRUE;
}
