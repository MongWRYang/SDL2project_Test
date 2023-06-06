#include<stdio.h>
#include<stdlib.h>
#include<time.h>
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

    SDL_Renderer *rend = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
    if(rend == NULL){
        SDL_Log("init Renderer Fail : %s\n",SDL_GetError());
        return 1;
    };

    int elfposx =80;
    int elfposy =100;

    SDL_SetRenderDrawColor(rend,255,255,255,255);
    //SDL_RenderClear(rend);
    SDL_RenderPresent(rend);
    SDL_Rect r = {600,300,50,50};
    SDL_Rect elf_r ={elfposx,elfposy,50,50};
    SDL_Surface *elf_surface = SDL_LoadBMP("img/elf.bmp");
    Uint32 colorkey = SDL_MapRGB(elf_surface->format, 255, 255, 255);
    SDL_SetColorKey(elf_surface, SDL_TRUE, colorkey);
    SDL_Texture *elf_texture = SDL_CreateTextureFromSurface(rend,elf_surface);
    SDL_FreeSurface(elf_surface);
    

    /* 繪製矩形的方法
    SDL_Rect r = {600,300,50,50};
    SDL_FillRect(sur,&r,0xfffff00);
    */

    /* 一個個像素的改變方法
    *(((uint32_t*)sur->pixels) + 50) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 51) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 52) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 850) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 851) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 852) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 1650) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 1651) = 0xfffff000;
    *(((uint32_t*)sur->pixels) + 1652) = 0xfffff000;
    */

    srand(time(NULL));
    printf("rand max %d \n",RAND_MAX);
    int x = 255;

    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;

    int window_exist = 1;
    while(window_exist){
        SDL_SetRenderDrawColor(rend,0,0,0,255);
        //SDL_SetRenderDrawBlendMode(rend,SDL_BLENDMODE_BLEND);
        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend,200,50,10,x);
        SDL_SetRenderDrawBlendMode(rend,SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(rend,&r);
        SDL_RenderCopy(rend,elf_texture,NULL,&elf_r);
        SDL_RenderPresent(rend);
        x--;
        if(SDL_PollEvent(&evt)){
            if(evt.type == SDL_QUIT){
                window_exist = 0;
            };
            if(evt.type == SDL_KEYDOWN){
                if(evt.key.keysym.scancode == SDL_SCANCODE_LEFT){
                    left = 1;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_RIGHT){
                    right = 1;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_UP){
                    up = 1;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_DOWN){
                    down = 1;
                }
            }
            if(evt.type == SDL_KEYUP){
                if(evt.key.keysym.scancode == SDL_SCANCODE_LEFT){
                    left = 0;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_RIGHT){
                    right = 0;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_UP){
                    up = 0;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_DOWN){
                    down = 0;
                }
            }
        };
        if(left){
            elf_r.x = elf_r.x-3;
        }
        if(right){
            elf_r.x = elf_r.x+3;
        }
        if(up){
            elf_r.y = elf_r.y-3;
        }
        if(down){
            elf_r.y = elf_r.y+3;
        }
        SDL_Delay(10);
    };

    SDL_DestroyTexture(elf_texture);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    return 0;
}