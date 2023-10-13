#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>

#include <stdio.h>

#include "lancolt_fugvenyek.h"
#include "sld_fuggvenyek.h"
#include "debugmalloc.h"
#include "strukturak.h"

struct KigyoElem *beszur(struct KigyoElem *eleje, struct Koordinatak adat){
    struct KigyoElem *uj_elem;
    uj_elem = (struct KigyoElem*) malloc(sizeof(struct KigyoElem));
    if (uj_elem == NULL){
        printf("Nem sikerult memoriat foglalni :(\n");
        return -1;
    }
    else
        printf("Lefoglaltunk %d byte memoriat\n",sizeof(struct KigyoElem));
    uj_elem -> adat = adat;
    uj_elem -> kov = eleje;
    return uj_elem;
}
void felszabadit(KigyoElem *eleje){
    KigyoElem *iter;
    iter = eleje;

    while (iter != NULL) {
        KigyoElem *kov = iter->kov;
        free(iter);
        iter = kov;
    }
}
Koordinatak ideszurbe(KigyoElem *eleje){
    KigyoElem *mozgo;
    mozgo = eleje;
    while (mozgo->kov != NULL){
        mozgo = mozgo->kov;
    }
    return mozgo->adat;
}
KigyoElem *hozzafuz(KigyoElem *eleje, Koordinatak adat){
    KigyoElem *uj;
    uj = (KigyoElem*) malloc(sizeof(KigyoElem));
    if (uj == NULL){
        printf("Nem sikerult memoriat foglalni :(\n");
        return -1;
    }
    else
        printf("Lefoglaltunk %d byte memoriat\n",sizeof(struct KigyoElem));
    uj->adat = adat;
    uj->kov = NULL;

    if (eleje == NULL) {
       /* �res list�n�l ez lesz az els� elem */
       eleje = uj;
    }
    else {
       /* ha nem �res a lista, az utols� ut�n f�zz�k */
       KigyoElem *mozgo = eleje;
       while (mozgo->kov != NULL)
          mozgo = mozgo->kov;
       mozgo->kov = uj;
    }
    return eleje;
}
KigyoElem *Kigyo_init(KigyoElem *eleje, int hossz, int ablak_szelesseg,int ablak_magassag,int oldal,int hezag){
    KigyoElem init;
    init.adat.x = (ablak_szelesseg/(oldal+hezag))/2;
    init.adat.y = (ablak_magassag/(oldal+hezag))/2;
    eleje = beszur(eleje,init.adat);
//    printf("%d %d\n",init.adat.x,init.adat.y);
//    eleje = beszur(eleje,init.adat);
    for (int i = 0; i < hossz-1; i++){
        init.adat.y += 1;
        eleje = hozzafuz(eleje,init.adat);
    }
    return eleje;
}
