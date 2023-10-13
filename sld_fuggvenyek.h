#ifndef SDL_FUGGVENYEK_H
#define SDL_FUGGVENYEK_H
#include "strukturak.h"
#include <stdbool.h>

Uint32 idozit(Uint32 ms, void *param);
void negyzet_rajzol_kord_szin(Koordinatak kord, int oldal, int hezag, Uint32 szin);
void negyzet_rajzol_kord_szin_lyukas(Koordinatak kord, int oldal, int hezag, Uint32 szin);
void karika_rajzol_kord_szin(Koordinatak kord, int oldal, int hezag, Uint32 szin);
void felso_keret(void);
void also_keret(void);
void bal_keret(void);
void jobb_keret(void);
void megrajzol_egesz_keret(void);
void kigyo_kirajzol(KigyoElem *eleje,Uint32 szin,bool ures);
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);

#endif // SDL_FUGGVENYEK_H
