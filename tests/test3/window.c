#include "window.h"

defconstructor(Window, int width, int height, char *title)
    self->width = width;
    self->height = height;

    self->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    self->renderer = SDL_CreateRenderer(self->window, -1, 0);

    self->closeRequested = 0;

    add_method(Window, FillRect)
    add_method(Window, SetColor)
    add_method(Window, Update)
    add_method(Window, Clear)
    add_method(Window, Flip)
    add_method(Window, isCloseRequested)
endconstructor

defmethod(Window, void, Clear)
    SDL_RenderClear(self->renderer);
endmethod

defmethod(Window, void, FillRect, int x, int y, int w, int h)
    SDL_Rect r = {x, y, w, h};
    SDL_RenderFillRect(self->renderer, &r);
endmethod

defmethod(Window, void, SetColor, int r, int g, int b, int a)
    SDL_SetRenderDrawColor(self->renderer, r, g, b, a);
endmethod

defmethod(Window, void, Update)
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                self->closeRequested = 1;
                break;
        }
    }
endmethod

defmethod(Window, void, Flip)
    SDL_RenderPresent(self->renderer);
endmethod

defmethod(Window, int, isCloseRequested)
    return self->closeRequested;
endmethod
