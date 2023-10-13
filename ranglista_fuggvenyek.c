#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>

#include <stdio.h>

#include "debugmalloc.h"
#include "strukturak.h"
void toplista_kiir(Sor *sor,int hossz,FILE *file){
    for (int i = 0;i < hossz;i++){
        fprintf(file,"%d %d %s\n",sor[i].helyezes,sor[i].pont,sor[i].nev);
    }
}
void buborek(Sor *t, int db) {
    /* egyre rövidebb tömbrészletek ciklusa */
    for (int i = db-1; i > 0; --i) {
        /* egymás utáni párok ciklusa */
        for (int j = 0; j < i; ++j) {
            if (t[j].pont <= t[j+1].pont) {
                struct Sor temp = t[j];
                t[j] = t[j+1];
                t[j+1] = temp;
            }
        }
    }
}
void helyezes_frissit(Sor *t,int db){
    for (int i = 0;i < db;i++){
        t[i].helyezes = i+1;
    }
}
