#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "debugmalloc.h"
#include "sld_fuggvenyek.h"
#include "jatek_fuggvenyek.h"
#include "strukturak.h"

int oldal;
int hezag;

void kigyo_leptet(struct KigyoElem *eleje,enum Irany irany){
    struct KigyoElem *mozgo;
    struct Koordinatak temp, temp2;

    temp.x = eleje->adat.x; temp.y = eleje->adat.y;
    if (irany == JOBBRA){
        eleje->adat.x += 1;
    }
    if (irany == LE){
        eleje->adat.y += 1;
    }
    if (irany == BALRA){
        eleje->adat.x -= 1;
    }
    if (irany == FEL) {
        eleje->adat.y -= 1;
    }
    mozgo = eleje->kov;
    while (mozgo != NULL){
        temp2.x = mozgo->adat.x; temp2.y = mozgo->adat.y;
        mozgo->adat.x = temp.x; mozgo->adat.y = temp.y;
        temp = temp2;
        mozgo = mozgo->kov;
    }
}
void random_pozicio_gen_alma(Koordinatak *alma,int ablak_szelesseg, int ablak_magassag,KigyoElem *eleje,KigyoElem *kigyo2){
    bool utkozik = true;
    while (utkozik){
        alma->x = (rand() % ((ablak_szelesseg/(oldal+hezag)-2) - 1 + 1)) + 1;                                               //a formula forrasa : https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx
        alma->y = (rand() % ((ablak_magassag/(oldal+hezag)-2) - 1 + 1)) + 1;
        KigyoElem *mozgo;
        utkozik = false;
        for (mozgo = eleje; mozgo != NULL;mozgo = mozgo->kov){
            if (alma->x == mozgo->adat.x && alma->y == mozgo->adat.y){
                utkozik = true;
                break;
            }
        }
        for (mozgo = kigyo2; mozgo != NULL;mozgo = mozgo->kov){
            if (alma->x == mozgo->adat.x && alma->y == mozgo->adat.y){
                utkozik = true;
                break;
            }
        }
    }
}
