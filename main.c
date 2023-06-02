#include<stdio.h>
#include<stdbool.h>
#include"SDL2src/include/SDL2/SDL.h"


int main(int argc,char* argv[]){
    printf("bit number = %d \n",8 * sizeof(void*));

    /*啟動SDL的資源，成功回傳0*/
    if(SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("init video Fail : %s\n",SDL_GetError());
        return 1;
    };

    SDL_Event evt;

    SDL_Window *win = SDL_CreateWindow("Eric Test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
    if(win == NULL){
        SDL_Log("Create Window Fail : %s\n",SDL_GetError());
        return 1;
    };

    SDL_Surface *sur = SDL_GetWindowSurface(win);
    SDL_Rect r = {20,20,20,20};
    SDL_FillRect(sur,&r,0xffffff00);
    *(((uint32_t*)sur->pixels) + 50) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 51) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 52) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 850) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 851) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 852) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 1650) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 1651) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 1652) = 0xfffff000;
    SDL_UpdateWindowSurface(win);

    int window_exist = 1;
    while(window_exist){
        if(SDL_PollEvent(&evt)){
            SDL_Log("event: %d",evt.type);
            if(evt.type == SDL_QUIT){
                window_exist = 0;
            };
        };
    };


    SDL_DestroyWindow(win);

    return 0;
}