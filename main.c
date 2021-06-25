#include<math.h>
#include<stdio.h>
#include "sound_meter.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (530)
#define WINDOW_HEIGHT (746)
#define INTENSITY (-16)

int main() {
  start_devices();
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("PNG tuber",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  
  if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
      printf("error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
    }

    //Sets the BG color
    SDL_SetRenderDrawColor(rend, 0, 255, 0, 0);
    // load the image into memory using SDL_image library function
    SDL_Surface* surface = IMG_Load("resources/cm.png");
    SDL_Surface* surface2 = IMG_Load("resources/om.png");
    if (!surface|!surface2)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_Texture* tex2 = SDL_CreateTextureFromSurface(rend, surface2);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);

    if (!tex|!tex2)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // struct to hold the position and size of the sprite
    SDL_Rect dest;

    // get and scale the dimensions of texture
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    /*float ratio;
    if (WINDOW_HEIGHT < WINDOW_WIDTH) {
       ratio =  WINDOW_HEIGHT / dest.h;
     } else {
       ratio = WINDOW_WIDTH /dest.w;
     }
     dest.w *= ratio;
     dest.h *= ratio;
    // start sprite in center of screen
    */

    // set to 1 when window close button is pressed
    int close_requested = 0;
    
    // animation loop
    while (!close_requested)
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                close_requested = 1;
            }
        }
               
        // clear the window
        SDL_RenderClear(rend);
        // draw the image to the window
        double vol = get_volume_level();
        dest.y = (int) log10(vol) * INTENSITY + 50;
        if (vol < 3000) {
          SDL_RenderCopy(rend, tex, NULL, &dest);
        } else {
          SDL_RenderCopy(rend, tex2, NULL, &dest);
        }
        SDL_RenderPresent(rend);

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }
    
    // clean up resources before exiting
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    destroy_volume_level(); 
  return 0;
}


