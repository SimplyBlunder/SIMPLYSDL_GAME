#include "./constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
// #include <SDL2/SDL_render.h>
// #include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

/*
 * Global Variables
 * */
int last_frame_time = 0;
int game_is_running = FALSE;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

/*
 * Delcare objects for the ball and paddle
 * */
struct game_objects {
  float x;
  float y;
  float width;
  float height;
} ball, paddle;

/*
 * Function to initialse SDL window
 * */
int initialise_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initalising SDL.\n");
    return FALSE;
  }

  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

  // error handiling for SDL window creation
  if (!window) {
    fprintf(stderr, "Error creating SDL Window.\n");
    return FALSE;
  }
  // error handiling for SDL renderer
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    fprintf(stderr, "Error creating SDL renderer.\n");
    return FALSE;
  }
  return TRUE;
}

// Switch Statement here handles the exit of the program using the ESC key.
// Wrapped in a while loop here to ensure it's constantly checking for key
// presses incase key before ESC was pressed.
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

/*
 * Setup function that runs once at the beginning of program
 * */
void setup() {
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

/*
 * Update function with a fixed time step
 * */
void update() {
  // sleep the execution until we reach the target frame time in milli.
  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

  // only call delay if we are too fast to process this frame.
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

/*
 * Function to draw game objects in SDL window
 * */
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

/*
 * Function to destroy SDL window and renderer
 * */
void destroy_window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

/*
 * Main function
 * */
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
