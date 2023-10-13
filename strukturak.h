#ifndef STRUKTURAK_H
#define STRUKTURAK_H

typedef struct Koordinatak{
    int x,y;
}Koordinatak;

typedef struct KigyoElem{
    Koordinatak adat;
    struct KigyoElem *kov;
}KigyoElem;

typedef struct Sor{
    int helyezes;
    int pont;
    char nev[100];
}Sor;

enum Irany{BALRA,JOBBRA,FEL,LE};

#endif // STRUKTURAK_H
