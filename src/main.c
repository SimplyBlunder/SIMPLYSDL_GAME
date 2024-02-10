#include "./constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
// #include <SDL2/SDL_render.h>
// #include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

int last_frame_time = 0;
int game_is_running = FALSE;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

struct game_objects {
  float x;
  float y;
  float width;
  float height;
} ball, paddle;

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
  // Spawning in objects.

  ball.x = 20;
  ball.y = 20;
  ball.width = 15;
  ball.height = 15;
  paddle.x = 20;
  paddle.y = 20;
  paddle.width = 15;
  paddle.height = 15;
}

void update() {
  // Waste some time until reach the frame target time
  // this should be changed later.. not nice solution. might use SDL_Delay to
  // cutback on resources.

  // sleep the execution until we reach the target frame time in milli.
  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

  // only call delay if we are too fast too process this frame.
  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
    SDL_Delay(time_to_wait);
  }

  float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

  last_frame_time = SDL_GetTicks();
  // setting object speed
  ball.x += 70 * delta_time;
  ball.y += 50 * delta_time;

  paddle.x += 20 * delta_time;
  paddle.y += 20 * delta_time;
}

void render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // draw a rectangle
  SDL_Rect ball_rect = {(int)ball.x, (int)ball.y, (int)ball.width,
                        (int)ball.height};

  // Drawing paddle for test purposes
  SDL_Rect paddle_rect = {(int)paddle.x, (int)paddle.y, (int)paddle.width,
                          (int)paddle.height};

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &ball_rect);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &paddle_rect);

  // Start drawing objets here
  // TWO buffers for swap
  SDL_RenderPresent(renderer);
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
