#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "sld_fuggvenyek.h"
#include "lancolt_fugvenyek.h"
#include "vizsgalo_fuggvenyek.h"
#include "ranglista_fuggvenyek.h"
#include "strukturak.h"
#include "debugmalloc.h"

#define nokiazold 0x9BCC0CFF
#define fekete 0x344E09FF

////////////////////////////////valtozok////////////////////////////////
int oldal = 15;
int hezag = 5;
int ablak_szelesseg;
int ablak_magassag;
int speed;

SDL_Renderer *renderer;


int main(int argc, char *argv[]) {
    //////////////////////////file beolvasas/////////////////////////
    FILE *file = fopen("leaderboard.txt","r");
    if (file == NULL){
        perror("A file megnyitasa sikertelen");
        getch();
        return 1;
    }
    if (file != NULL){
        printf("Sikeresen megtalaltam es beolvastam a leaderboard.txt filet!\n\n");
    }
    Sor sor;
    Sor regi[10];

    int i = 0;
    while (!feof(file)){
        fscanf(file, "%d %d %[^\n]", &sor.helyezes, &sor.pont, sor.nev);
        regi[i] = sor;
        i++;
    }
    fclose(file);
    //////////////////////////file beolvasas/////////////////////////

    bool tobbjatekos = false;

    int valasz;
    /////////////////////////////////////////////////////////////////////////////////////////////

    printf("Szia. Udv a Snek jatekomban. Kerlek valaszd ki a jatekmodot palyameretet es a sebesseged.\nA valaszok beirasa utan nyomj ENTERT!\nIranyitas:\nTeli balra/jobbra/fel/le nyilak\nUres WASD\n\n");

    /////////////////////////////////////////////////////////////////////////////////////////////

    printf("1: egyjatekos mod\n2: ketjatekos mod\n3: ranglista\n\nValaszod: ");
    scanf("%d",&valasz);
    if (valasz < 1 || valasz > 3){
        printf("Ez nem jo valasz!\nIrj be masikat\n");
        while (valasz < 1 || valasz > 3){
            scanf("%d",&valasz);
        }
    }
    switch (valasz){
        case 1: break;
        case 2: tobbjatekos = true; break;
        case 3: {
            for (int i = 0;i < 10;i++){
                printf("%d %d %s\n",regi[i].helyezes,regi[i].pont,regi[i].nev);
            }
            printf("\nNyomj ENTERT a kilepeshez\n");
            getch();
            return 1; break;
        }
    }
    printf("Palyameret:\n1: kicsi\n2: kozepes\n3: nagy\n");
    int meret;
    scanf("%d",&meret);
    if (meret < 1 || meret > 3){
        printf("Ez nem jo valasz!\nIrj be masikat\n");
        while (meret < 1 || meret > 3){
            scanf("%d",&meret);
        }
    }
    switch(meret){
        case 1: ablak_szelesseg = 20*(oldal+hezag); ablak_magassag = 20*(oldal+hezag); break;
        case 2: ablak_szelesseg = 40*(oldal+hezag); ablak_magassag = 40*(oldal+hezag); break;
        case 3: ablak_szelesseg = 50*(oldal+hezag); ablak_magassag = 50*(oldal+hezag); break;
    }
    printf("Sebesseg(fentrol lefele nehezedik) :\n1000-500 -> Mernok leszek\n500-300  -> Bevezet fizika\n300-200  -> programozas alapjai\n200-150  -> analizis\n150-100  -> bsz1\n100-1    -> GOOD LUCK M8\n\nValaszod: ");
    scanf("%d",&speed);
    if (speed < 1 || speed > 1000){
        printf("Ez nem jo valasz! Irj be masikat\n");
        while (speed < 1 || speed > 1000){
            scanf("%d",&speed);
        }
    }

    ////////////////////////////////ablak keszites//////////////////////////
    SDL_Window *window;
    sdl_init("Snaek", ablak_szelesseg, ablak_magassag, &window, &renderer);
    SDL_TimerID id = SDL_AddTimer(speed,idozit,NULL);
    srand(time(NULL));
    SDL_RaiseWindow(window);
    ////////////////////////////////ablak keszites//////////////////////////

    ////////////////////////////////inicializalasok/////////////////////////
    Koordinatak alma;
    Koordinatak *palma = &alma;
    palma->x = -1;
    palma->y = -1;

    KigyoElem *eleje;
    eleje = NULL;
    KigyoElem *kigyo2;
    kigyo2 = NULL;
    ////////////////////////////////inicializalasok/////////////////////////

    ////////////////////////////////valtozok////////////////////////////////
    int hossz1 = 4;
    int hossz2 = 4;
    int pont1 = 1;
    int pont2 = 1;
    bool quit = false;
    bool quit2 = false;
    bool quit3 = false;
    bool van_alma = false;
    bool nyomott_gombot1 = false;
    bool nyomott_gombot2 = false;
    Koordinatak temp;
    enum Irany irany1 = FEL;
    enum Irany irany2 = FEL;
    ////////////////////////////////valtozok////////////////////////////////

    eleje = Kigyo_init(eleje,hossz1,ablak_szelesseg,ablak_magassag,oldal,hezag);
    if (tobbjatekos)
        kigyo2 = Kigyo_init(kigyo2,hossz2,ablak_szelesseg+10*(oldal+hezag),ablak_magassag,oldal,hezag);

    while (!quit && !quit2 && !quit3){
        SDL_Event event;
        SDL_WaitEvent(&event);

        SDL_SetRenderDrawColor(renderer,155,204,12,255);
        SDL_RenderClear(renderer);

        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_LEFT:    if (irany1 != JOBBRA && !nyomott_gombot1)  irany1 = BALRA;  nyomott_gombot1 = true; break;
                    case SDLK_RIGHT:   if (irany1 != BALRA && !nyomott_gombot1)   irany1 = JOBBRA; nyomott_gombot1 = true; break;
                    case SDLK_UP:      if (irany1 != LE && !nyomott_gombot1)      irany1 = FEL;    nyomott_gombot1 = true; break;
                    case SDLK_DOWN:    if (irany1 != FEL && !nyomott_gombot1)     irany1 = LE;     nyomott_gombot1 = true; break;

                    case SDLK_a:       if (irany2 != JOBBRA && !nyomott_gombot2)  irany2 = BALRA;  nyomott_gombot2 = true; break;
                    case SDLK_d:       if (irany2 != BALRA && !nyomott_gombot2)   irany2 = JOBBRA; nyomott_gombot2 = true; break;
                    case SDLK_w:       if (irany2 != LE && !nyomott_gombot2)      irany2 = FEL;    nyomott_gombot2 = true; break;
                    case SDLK_s:       if (irany2 != FEL && !nyomott_gombot2)     irany2 = LE;     nyomott_gombot2 = true; break;

                    case SDLK_SPACE:   {hossz1++;
                                        pont1++;
                                        temp = ideszurbe(eleje);
                                        eleje = hozzafuz(eleje,temp);
                                        }break;

                    case SDLK_ESCAPE:            quit2 = true; quit = true;   break;
                }
                break;
            case SDL_QUIT:
                quit = true;
                break;
        }
        switch (event.type){
            case SDL_USEREVENT:{
                kigyo_leptet(eleje,irany1);
                nyomott_gombot1 = false;
                nyomott_gombot2 = false;
                quit  = falnak_megy_e(eleje,ablak_szelesseg,ablak_magassag) || maganak_megy_e(eleje) || masnak_megy_e(eleje,kigyo2);
                if (tobbjatekos)
                    kigyo_leptet(kigyo2,irany2);
                if (van_alma == false){
                    random_pozicio_gen_alma(palma,ablak_szelesseg,ablak_magassag,eleje,kigyo2);
                    van_alma = true;
                }
                if (tobbjatekos){
                    quit2 = falnak_megy_e(kigyo2,ablak_szelesseg,ablak_magassag) || maganak_megy_e(kigyo2) || masnak_megy_e(kigyo2,eleje);
                    quit3 = (quit && quit2);
                }
                if (evett_e(eleje,palma)){
                    van_alma = false;
                    hossz1++;
                    pont1++;
                    temp = ideszurbe(eleje);
                    eleje = hozzafuz(eleje,temp);
                }
                if (tobbjatekos){
                    if (evett_e(kigyo2,palma)){
                        van_alma = false;
                        hossz2++;
                        pont2++;
                        temp = ideszurbe(kigyo2);
                        kigyo2 = hozzafuz(kigyo2,temp);
                    }
                }
            }
            break;
        }
        megrajzol_egesz_keret();
        karika_rajzol_kord_szin(*palma,oldal,hezag,fekete);
        kigyo_kirajzol(eleje,fekete,false);
        if (tobbjatekos){
            kigyo_kirajzol(kigyo2,fekete,true);
            char pontkiir2[5];
            sprintf(pontkiir2,"ures pont %d",pont2);
            stringRGBA(renderer,ablak_szelesseg/4*2,oldal+2*hezag,pontkiir2,52,78,9,255);
        }
        char pontkiir1[5];
        sprintf(pontkiir1,"teli pont %d",pont1);
        stringRGBA(renderer,ablak_szelesseg/4,oldal+2*hezag,pontkiir1,52,78,9,255);
        SDL_RenderPresent(renderer);
    }
    felszabadit(eleje);
    felszabadit(kigyo2);
    SDL_Quit();
    SDL_RemoveTimer(id);
    if (tobbjatekos){
        if (quit3){
            printf("Kocc\nNem nyert senki :(\n");
            quit = false;
            quit2 = false;
        }
        else if (quit){
            printf("Az ures nyert!\n");
        }
        else if (quit2){
            printf("A teli nyert!\n");
        }

    }
    else{
        char temp;
        printf("Meghaltal PONTOD: %d\n",pont1);
        if (pont1 >= regi[10].pont){
            Sor uj = {11,pont1,"NA"};
            printf("Hogy hivnak? ");
            scanf("%c",&temp);
            scanf("%[^\n]",uj.nev);
            regi[10] = uj;
            buborek(regi,11);
            file = fopen("leaderboard.txt","w");
            helyezes_frissit(regi,11);
            toplista_kiir(regi,10,file);
            fclose(file);
        }


    }
    printf("\nNyomj ENTERT a kilepeshez\n");
    getch();
    return 0;
}
