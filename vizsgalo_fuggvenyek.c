#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "sld_fuggvenyek.h"
#include "strukturak.h"
#include "debugmalloc.h"


int oldal;
int hezag;

bool evett_e(KigyoElem *eleje, Koordinatak *palma){
    if ((eleje->adat.x == palma->x) && (eleje->adat.y == palma->y)){
//        printf("---evett---\n");
        return true;
    }
    else{
        return false;
    }
}
bool falnak_megy_e(KigyoElem *eleje, int ablak_szelesseg, int ablak_magassag){
    if (eleje->adat.x <= ablak_szelesseg%(oldal+hezag) ||
        eleje->adat.y <= ablak_magassag%(oldal+hezag) ||
        eleje->adat.x >= ablak_szelesseg/(oldal+hezag)-1 ||
        eleje->adat.y >= ablak_magassag/(oldal+hezag)-1
        )
        return true;
    else
        return false;
}
bool maganak_megy_e(KigyoElem *eleje){
    KigyoElem *mozgo;
    for (mozgo = eleje->kov;mozgo != NULL;mozgo = mozgo->kov){
        if (eleje->adat.x == mozgo->adat.x &&
            eleje->adat.y == mozgo->adat.y){
                return true;
        }
    }
    return false;
}
bool masnak_megy_e(KigyoElem *eleje, KigyoElem *kigyo2){
    KigyoElem *mozgo;
    for (mozgo = kigyo2;mozgo != NULL;mozgo = mozgo->kov){
        if (mozgo->adat.x == eleje->adat.x && mozgo->adat.y == eleje->adat.y)
            return true;
    }
    return false;
}
