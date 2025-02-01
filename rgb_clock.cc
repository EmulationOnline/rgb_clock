#include <SDL2/SDL.h>

const int GFX_WIDTH = 256;
const int GFX_HEIGHT = 240;
const int BYTES_PER_PIXEL = 4;

// The display framebuffer is organized row major, and bytes within a pixel are in the order
// R,G,B,A
//               (x,y)
// So byte[0] is (0,0).r,
//    byte[1] is (0,0).g
//    ...
//    byte(4) is (1, 0).r
//    and so forth
uint32_t frame_buffer[GFX_WIDTH * GFX_HEIGHT];

void display_clear() {
    for (int i = 0; i < GFX_WIDTH*GFX_HEIGHT; i++) {
        // initialize all pixels as blue
        frame_buffer[i] = 0xFFFF0000;
    }
}

bool run;
const uint8_t *sdlkeys;
void handle_input() {
    for (SDL_Event event; SDL_PollEvent(&event);) {
        if (event.type == SDL_QUIT) {
            run = 0;
        }
    }
}

void update_display(uint32_t frames) {
    const int BAR_WIDTH_PX = 4;
    int cycle_offset = frames % GFX_HEIGHT*2;
    int bar_y_start = cycle_offset < GFX_HEIGHT
        // moving down
        ? cycle_offset
        // moving back up
        : GFX_HEIGHT - (cycle_offset - GFX_HEIGHT);

    for (int y = 0; y < GFX_HEIGHT; y++) {
        bool bar = false;
        if (y >= bar_y_start && y < bar_y_start + BAR_WIDTH_PX) {
            bar = true;
        }

        for (int x = 0; x < GFX_WIDTH; x++) {
            uint32_t pixel = 0xFF000000;
            uint8_t r = x;
            uint8_t g = y;
            uint8_t b = 255;
            pixel |= r | (g<<8) | (b<<16);
            frame_buffer[y*GFX_WIDTH + x] = 
                bar ? 0xFF000000
                    : pixel;
        }
    }
}

int main(void) {
  SDL_Init(SDL_INIT_VIDEO);
  // draw a screen 4x the native size
  SDL_Renderer *renderer = SDL_CreateRenderer(
      SDL_CreateWindow("rgb clock demo", 0, 0, 1000, 960, SDL_WINDOW_SHOWN), -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_Texture *texture = SDL_CreateTexture(
      renderer, 
      SDL_PIXELFORMAT_RGBA32,
      SDL_TEXTUREACCESS_STREAMING, 
      256, 224);
  display_clear();
  run = true;
  uint32_t frames = 0;
  while(run) {
      handle_input();
      update_display(frames);
      SDL_UpdateTexture(texture, 0, frame_buffer, GFX_WIDTH*BYTES_PER_PIXEL);
      SDL_RenderCopy(renderer, texture, 0, 0);
      SDL_RenderPresent(renderer);
      frames += 1;
  }
  return 0;
}
