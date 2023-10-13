#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "sld_fuggvenyek.h"
#include "strukturak.h"
#include "debugmalloc.h"
#define feher 0xFFFFFFFF
#define fekete 0x344E09FF

SDL_Renderer *renderer;
extern int oldal;
extern int hezag;
extern int ablak_szelesseg;
extern int ablak_magassag;

Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}
void negyzet_rajzol_kord_szin(Koordinatak kord, int oldal, int hezag, Uint32 szin){
    int x = kord.x*(oldal+hezag);
    int y = kord.y*(oldal+hezag);
    boxColor(renderer,x,y,x+oldal,y+oldal,szin);
}
void negyzet_rajzol_kord_szin_lyukas(Koordinatak kord, int oldal, int hezag, Uint32 szin){
    int x = kord.x*(oldal+hezag);
    int y = kord.y*(oldal+hezag);
    rectangleColor(renderer,x,y,x+oldal,y+oldal,szin);
}
void karika_rajzol_kord_szin(Koordinatak kord, int oldal, int hezag, Uint32 szin){
    int x = kord.x*(oldal+hezag)+(oldal/2);
    int y = kord.y*(oldal+hezag)+(oldal/2);
    int r = oldal/2;
    circleColor(renderer,x,y,r,fekete);
}
void felso_keret(void){
    Koordinatak kord = {0,0};
    while(kord.x < ablak_szelesseg/(oldal+hezag)){
        negyzet_rajzol_kord_szin(kord,oldal,hezag,fekete);
        kord.x += 1;
    }
}
void also_keret(void){
    Koordinatak kord = {0,ablak_magassag/(oldal+hezag)-1};
    while (kord.x < ablak_szelesseg/(oldal+hezag)){
        negyzet_rajzol_kord_szin(kord,oldal,hezag,fekete);
        kord.x += 1;
    }
}
void bal_keret(void){
        Koordinatak kord = {0,0};
        while(kord.y < ablak_magassag/(oldal+hezag)){
        negyzet_rajzol_kord_szin(kord,oldal,hezag,fekete);
        kord.y += 1;
    }
}
void jobb_keret(void){
    Koordinatak kord = {ablak_szelesseg/(oldal+hezag)-1,0};
    while(kord.y < ablak_magassag/(oldal+hezag)){
        negyzet_rajzol_kord_szin(kord,oldal,hezag,fekete);
        kord.y += 1;
    }
}
void megrajzol_egesz_keret(void){
    felso_keret();
    also_keret();
    bal_keret();
    jobb_keret();
}
void kigyo_kirajzol(KigyoElem *eleje,Uint32 szin,bool ures){
    KigyoElem *mozgo;
    for (mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov){
        if(!ures)
            negyzet_rajzol_kord_szin(mozgo->adat,oldal,hezag,szin);
        else
            negyzet_rajzol_kord_szin_lyukas(mozgo->adat,oldal,hezag,szin);
    }
}
