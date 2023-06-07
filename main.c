#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"SDL2src/include/SDL2/SDL.h"

#define snake_maxlength 200

int s_length = 20;
int s_left,s_right,s_up,s_down = 0;
int window_w = 800;
int window_h = 600;

struct snake{
    SDL_Rect snake_r;
};

struct food{
    SDL_Rect food_rect;
    int exist;
};

int randnum(int min,int max){
    double randmax = RAND_MAX;
    int result = (rand()/randmax)*max + min;
    return result;
};

/*測試r1的頂點是否在r2之內*/
int Check_Rect_include(SDL_Rect *r1,SDL_Rect *r2){
    int p1[2] ={r1->x,r1->y};
    int p2[2] ={(r1->x)+(r1->w),r1->y};
    int p3[2] ={(r1->x)+(r1->w),(r1->y)+(r1->h)};
    int p4[2] ={r1->x,(r1->y)+(r1->h)};

    if( ((r2->x) < p1[0])&&(p1[0]<(r2->x)+(r2->w))){
        if(((r2->y) < p1[1])&&(p1[1]<(r2->y)+(r2->h))){
            return 1;
        }
    }
    if( ((r2->x) < p2[0])&&(p2[0]<(r2->x)+(r2->w))){
        if(((r2->y) < p2[1])&&(p2[1]<(r2->y)+(r2->h))){
            return 1;
        }
    }
    if( ((r2->x) < p3[0])&&(p3[0]<(r2->x)+(r2->w))){
        if(((r2->y) < p3[1])&&(p3[1]<(r2->y)+(r2->h))){
            return 1;
        }
    }
    if( ((r2->x) < p4[0])&&(p4[0]<(r2->x)+(r2->w))){
        if(((r2->y) < p4[1])&&(p4[1]<(r2->y)+(r2->h))){
            return 1;
        }
    }
    return 0;
}

/*測試r1是否與r2相交*/
int Check_Rect_overlap(SDL_Rect *r1,SDL_Rect *r2){
    if (Check_Rect_include(r1,r2)||Check_Rect_include(r2,r1)){
        return 1;
    }
    return 0;
}

void Printfood(struct food f,SDL_Renderer* rend){
    if(f.exist){
        SDL_SetRenderDrawColor(rend,180,150,10,255);
        SDL_RenderFillRect(rend,&f.food_rect);
    }
};

void Printsnake(struct snake* s,SDL_Renderer* rend,SDL_Texture *textu){
    SDL_SetRenderDrawColor(rend,0,255,0,255);
    for (int i=1;i<s_length;i++){
        SDL_RenderFillRect(rend,&s[i].snake_r);
    }
    SDL_RenderCopy(rend,textu,NULL,&s[0].snake_r);
};

void Movesnake(struct snake* s,int fang){
    for(int i=snake_maxlength-1;i>0;i--){
        s[i].snake_r.x = s[i-1].snake_r.x;
        s[i].snake_r.y = s[i-1].snake_r.y;
    }
    if(fang == 1){
        s[0].snake_r.x = s[1].snake_r.x - 3;
    }else if(fang == 2){
        s[0].snake_r.x = s[1].snake_r.x + 3;
    }else if(fang == 3){
        s[0].snake_r.y = s[1].snake_r.y - 3;
    }else if(fang == 4){
        s[0].snake_r.y = s[1].snake_r.y + 3;
    }
    if(s[0].snake_r.x > window_w){
        s[0].snake_r.x = 0;
    }
    if(s[0].snake_r.x < 0){
        s[0].snake_r.x = window_w;
    }
    if(s[0].snake_r.y > window_h){
        s[0].snake_r.y = 0;
    }
    if(s[0].snake_r.y < 0){
        s[0].snake_r.y = window_h;
    }
};

void Snake_add(){
    if(s_length < snake_maxlength){
        s_length=s_length+6;
    }
}



int main(int argc,char* argv[]){

    /*啟動SDL的資源，成功回傳0*/
    if(SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("init video Fail : %s\n",SDL_GetError());
        return 1;
    };

    SDL_Event evt;
    SDL_Window *win = SDL_CreateWindow("貪食蟲",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,window_w,window_h,SDL_WINDOW_SHOWN);
    if(win == NULL){
        SDL_Log("Create Window Fail : %s\n",SDL_GetError());
        return 1;
    };
    SDL_Renderer *rend = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
    if(rend == NULL){
        SDL_Log("init Renderer Fail : %s\n",SDL_GetError());
        return 1;
    };

    SDL_SetRenderDrawColor(rend,255,255,255,255);
    SDL_RenderPresent(rend);
    SDL_Surface *elf_surface = SDL_LoadBMP("img/elf.bmp");
    Uint32 colorkey = SDL_MapRGB(elf_surface->format, 255, 255, 255);
    SDL_SetColorKey(elf_surface, SDL_TRUE, colorkey);
    SDL_Texture *elf_texture = SDL_CreateTextureFromSurface(rend,elf_surface);
    SDL_FreeSurface(elf_surface);

    /*初始化蛇*/
    struct snake s[snake_maxlength];
    s[0].snake_r.h = 34;
    s[0].snake_r.w = 34;
    s[0].snake_r.x = 200;
    s[0].snake_r.y = 97;
    for(int i=1;i<snake_maxlength;i++){
        s[i].snake_r.h = 30;
        s[i].snake_r.w = 30;
        s[i].snake_r.x = 200;
        s[i].snake_r.y = 100+i*3;
    }

    /*初始化食物*/
    struct food food1;
    food1.food_rect.h = 60;
    food1.food_rect.w = 60;
    food1.food_rect.x = 500;
    food1.food_rect.y = 400;
    food1.exist = 1;

    srand(time(NULL));

    int window_exist = 1;
    while(window_exist){
        SDL_SetRenderDrawColor(rend,0,0,0,255);
        //SDL_SetRenderDrawBlendMode(rend,SDL_BLENDMODE_BLEND);
        SDL_RenderClear(rend);

        Printsnake(s,rend,elf_texture);
        Printfood(food1,rend);

        SDL_RenderPresent(rend);

        if(SDL_PollEvent(&evt)){
            if(evt.type == SDL_QUIT){
                window_exist = 0;
            };
            if(evt.type == SDL_KEYDOWN){
                if(evt.key.keysym.scancode == SDL_SCANCODE_LEFT){
                    s_left = 1;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_RIGHT){
                    s_right = 1;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_UP){
                    s_up = 1;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_DOWN){
                    s_down = 1;
                }
            }
            if(evt.type == SDL_KEYUP){
                if(evt.key.keysym.scancode == SDL_SCANCODE_LEFT){
                    s_left = 0;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_RIGHT){
                    s_right = 0;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_UP){
                    s_up = 0;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_DOWN){
                    s_down = 0;
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_S){
                    Snake_add();
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_Q){
                    if(!food1.exist){
                        food1.food_rect.x = randnum(0,772);
                        food1.food_rect.y = randnum(0,572);
                        food1.exist = 1;
                    }else{
                        food1.exist = 0;
                    }
                }
                if(evt.key.keysym.scancode == SDL_SCANCODE_P){
                    printf("inc result: %d \n",Check_Rect_include(&food1.food_rect,&s[0].snake_r));
                    printf("over result: %d \n",Check_Rect_overlap(&food1.food_rect,&s[0].snake_r));
                }
            }
        };
        if(s_left == 1){
            Movesnake(s,1);
        }
        else if(s_right == 1){
            Movesnake(s,2);
        }
        else if(s_up == 1){
            Movesnake(s,3);
        }
        else if(s_down == 1){
            Movesnake(s,4);
        }
        SDL_Delay(10);
    };

    SDL_DestroyTexture(elf_texture);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    return 0;
}