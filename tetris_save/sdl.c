#include <SDL2/SDL.h>
#include <stdio.h>
#include "sdl.h"

void dessiner_rectangle(SDL_Renderer* pRenderer, int x, int y, int w, int h, SDL_Color couleur) {
    SDL_Rect rectangle = {x, y, w, h};
    if (SDL_SetRenderDrawColor(pRenderer, couleur.r, couleur.g, couleur.b, couleur.a) < 0)
        error_sdl_launch("Impossible de dessiner la couleur");
    if (SDL_RenderFillRect(pRenderer, &rectangle) < 0)
        error_sdl_launch("Impossible de dessiner les blocs");
}

void afficher_terrain(SDL_Window* Fenetre, SDL_Renderer* pRenderer, Case terrain[LARGEUR_TERRAIN][HAUTEUR_TERRAIN]) {
    if (Fenetre == NULL) {
        error_sdl_launch("Impossible de créer la fenêtre");
    }
    if (pRenderer == NULL) {
        error_sdl_launch("Impossible de créer le renderer");
    }
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer); //nettoyer l'écran

    int facteur = TAILLE_BLOCK + 5; //le facteur corespond à TAILLE_BLOCK + l'espacement désiré sur les blocks
    for (int y = 0; y<HAUTEUR_TERRAIN*facteur; y+=facteur) {
        for (int x = 0; x<LARGEUR_TERRAIN*facteur; x+=facteur) {
            printf("%d",terrain[x/facteur][y/facteur].valeur);
            //printf(" %d,%d ",x/facteur, y/facteur);
            dessiner_rectangle(pRenderer, x, y, TAILLE_BLOCK, TAILLE_BLOCK, terrain[x/facteur][y/facteur].couleur);//diviser par le facteur pour que les valleurs aillent de 0 à 19
        }
        printf("\n");
    }
    SDL_RenderPresent(pRenderer);
    printf("\n\n");
}

void error_sdl_launch(char* message) {
    fprintf(stderr,"%s, %s\n", message, SDL_GetError());
    exit(EXIT_FAILURE);
}

void event_clavier(SDL_Event *event, Case terrain[LARGEUR_TERRAIN][HAUTEUR_TERRAIN]) {
    while (SDL_PollEvent(event)) {
        puts("Event ?");
        if (event->type == SDL_KEYDOWN) {
            puts("KEYDOWN");
            switch (event->key.keysym.scancode) {
            case SDL_SCANCODE_RIGHT:
                printf("Flèche droite\n");
                break;

            case SDL_SCANCODE_ESCAPE:
                printf("Au revoir\n");
                exit(EXIT_SUCCESS);
                break;
            }
        }
        if (event->type  == SDL_QUIT) {
            printf("Au revoir\n");
            exit(EXIT_SUCCESS);
        }
    }
}
