#ifndef LANCOLT_FUGGVENYEK_H
#define LANCOLT_FUGGVENYEK_H
#include "sld_fuggvenyek.h"

struct KigyoElem *beszur(struct KigyoElem *eleje, struct Koordinatak adat);
void felszabadit(KigyoElem *eleje);
Koordinatak ideszurbe(KigyoElem *eleje);
KigyoElem *hozzafuz(KigyoElem *eleje, Koordinatak adat);
KigyoElem *Kigyo_init(KigyoElem *eleje, int hossz, int ablak_szelesseg,int ablak_magassag,int oldal,int hezag);


#endif // LANCOLT_FUGGVENYEK_H
