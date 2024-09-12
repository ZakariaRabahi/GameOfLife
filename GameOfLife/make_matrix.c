//
// Created by zk on 16/12/22.
//
#include <stdio.h>
#include <stdbool.h>
#include "make_matrix.h"

#define M 22
#define N 22

#define CELL_PX 20

#define WINDOW_WIDTH M*N
#define WINDOW_HEIGHT M*N


static SDL_Window *window;
static SDL_Renderer *renderer;


typedef struct {
    int totaal_buren;
    char type_buren;
} neighbours;

typedef struct {
    bool alive;
    char type;
} cell;


cell world[M][N];
cell next_world[M][N];


cell Create_cell(bool life, char type_of_cell){
    cell c;
    c.alive = life;
    c.type = type_of_cell;
    return c;
}

int copy_matrix() {
    for (int y = 0; y < M ; y++) {
        for (int x = 0; x < N ; x++) {
            world[y][x] = next_world[y][x];
        }
    }
    return 0;
}

void save_matrix() {
    FILE* fp = fopen("Saved_Matrix.txt", "w");
    if (fp == NULL) {
        // Error opening file
        return;
    }

    //fprintf(fp, "%d", WINDOW_WIDTH);
   // fprintf(fp, "\n");
   // fprintf(fp, "%d", WINDOW_WIDTH);
   // fprintf(fp, "\n");
   // fprintf(fp, "\n");


    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            fprintf(fp, "%c", world[y][x].type);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int matrix_make_zero(){

    for (int y = 0; y < M ; y++) {
        for (int x = 0; x < N; x++) {
            world[y][x] = Create_cell(false, 'X');
        }
    }
    return 0;
}

int init_matrix(){

    world[7][6] = Create_cell(true, 'A');
    world[6][4] = Create_cell(true, 'A');
    world[4][6] = Create_cell(true, 'B');
    world[15][17] = Create_cell(true, 'B');
    world[14][17] = Create_cell(true, 'B');
    world[15][18] = Create_cell(true, 'A');
    world[15][16] = Create_cell(true, 'A');

    world[5][5] = Create_cell(true, 'B');
    world[6][6] = Create_cell(true, 'A');
    world[7][6] = Create_cell(true, 'B');
    world[7][5] = Create_cell(true, 'A');
    world[7][4] = Create_cell(true, 'B');

    return 0;
}



int look_for_neighbours_type(int x, int y, char type){
    if (world[y][x].type == type){
        return 1;
    }
    else
    {return 0;
    }
}


neighbours count_neighbours(int x, int y){
    int type_A;
    int type_B;

    neighbours N1 = {0, 'X'};

    type_A = look_for_neighbours_type(x-1, y-1, 'A') + look_for_neighbours_type(x, y-1, 'A') + look_for_neighbours_type(x+1, y-1, 'A') +
             look_for_neighbours_type(x-1, y, 'A')       +                        0                      + look_for_neighbours_type(x+1, y, 'A') +
             look_for_neighbours_type(x-1, y+1, 'A')  + look_for_neighbours_type(x, y+1, 'A') + look_for_neighbours_type(x+1, y+1, 'A');

    type_B = look_for_neighbours_type(x-1, y-1, 'B') + look_for_neighbours_type(x, y-1, 'B') + look_for_neighbours_type(x+1, y-1, 'B') +
             look_for_neighbours_type(x-1, y, 'B')       +                        0                      + look_for_neighbours_type(x+1, y, 'B') +
             look_for_neighbours_type(x-1, y+1, 'B')  + look_for_neighbours_type(x, y+1, 'B') + look_for_neighbours_type(x+1, y+1, 'B');

    N1.totaal_buren = type_A + type_B;

    if (type_A < type_B){
        N1.type_buren = 'B';
    }
    else
    {
        N1.type_buren = 'A';
    }

    return N1;
}


int update_matrix(){
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            // if alive
            if (world[y][x].alive) {
                // kill
                if (count_neighbours(x, y).totaal_buren < 2 || count_neighbours(x, y).totaal_buren > 3) {
                    next_world[y][x] = Create_cell(false, 'X');
                }

                if (count_neighbours(x, y).totaal_buren == 2 || count_neighbours(x, y).totaal_buren == 3) {
                    next_world[y][x] = Create_cell(true, world[y][x].type);
                }
            }
                // if dead
            else {
                //back to life
                if (count_neighbours(x, y).totaal_buren == 3) {

                    next_world[y][x] = Create_cell(true, count_neighbours(x, y).type_buren);
                }

                else
                {
                    next_world[y][x] = world[y][x];
                }
            }

            printf("%c", world[x][y].type);
        }
        printf("\n");
    }
    copy_matrix();
    return 0;
}



int print_matrix(int number_of_times){

    for (int i = 0; i < number_of_times; i++){
        update_matrix();
        printf("\n");
        printf("\n");
        printf("\n");

    }


    return 0;
}


int is_relevant_event(SDL_Event *event) {
    if (event == NULL) {
        return 0;
    }
    return (event->type == SDL_QUIT);
}
/*
 * Vangt de input uit de GUI op. Deze functie is al deels geïmplementeerd, maar je moet die zelf
 * nog afwerken. Je mag natuurlijk alles aanpassen aan deze functie, inclusief return-type en argumenten.
 */


void clear_window() {
    /*
     * Maakt van wit de achtergrondkleur.
     */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    /*
     * Reset het venster en verandert het naar de kleur die op de lijn hierboven werd vastgelegd.
     */
    SDL_RenderClear(renderer);
}

void draw_rectangle(int x, int y, int width, int height) {
    /*
     * DPI_SCALING is ofwel 1, ofwel 2, afhankelijk van je platform: 2 voor moderne OSX systemen en 1 voor alle andere platformen.
     * Op moderne OSX systemen moet voor Retina displays expliciet de dimensies van getekende figuren verdubbeld worden,
     * aangezien die een hogere dpi hebben: figuren worden half zo klein voorgesteld zodat ze aan een hogere resolutie
     * kunnen getoond worden. Daarom verdubbelen we de positie en dimensies van de figuren zodat ze hun oorspronkelijke
     * positie en dimensie behouden.
     */
    SDL_Rect rectangle = { x * DPI_SCALING, y * DPI_SCALING, width * DPI_SCALING, height * DPI_SCALING};
    /* Vraagt de renderer om rectangle te tekenen, in de kleur die werd vastgelegd via SDL_SetRenderDrawColor. */
    SDL_RenderFillRect(renderer, &rectangle);
}

void draw_window() {
    clear_window();
    for (int y = 0; y < M ; y++) {
        for (int x = 0; x < N ; x++) {

            if (world[y][x].type == 'B') {
                SDL_SetRenderDrawColor(renderer, 255, 155, 140, 255);
                draw_rectangle(x * CELL_PX, y * CELL_PX, CELL_PX, CELL_PX);
            }

            if (world[y][x].type == 'A') {
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                draw_rectangle(x * CELL_PX, y * CELL_PX, CELL_PX, CELL_PX);
            }

        }
    }
    SDL_RenderPresent(renderer);
}

/*
 * Initialiseert het venster en alle andere structuren die gebruikt worden door de GUI.
 */
void initialize_window(const char *title) {
    /*
     * Code o.a. gebaseerd op http://lazyfoo.net/tutorials/SDL/02_getting_an_image_on_the_screen/index.php
     */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error while initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /*
     * Maakt het venster aan met gevraagde dimensies.
     * De titel van het venster zal overeenkomen met de waarde van de title-string.
     */
    window = SDL_CreateWindow(title, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL) {
        printf("Error: %s\n", SDL_GetError());
        exit(1);
    }

    /* Initialiseert de renderer. */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
}

/*
 * Dealloceert alle SDL structuren die dynamisch gealloceerd werden.
 */
void free_gui() {
    /* Dealloceert het venster. */
    SDL_DestroyWindow(window);
    /* Dealloceert de renderer. */
    SDL_DestroyRenderer(renderer);
    /* Stopt SDL. */
    SDL_Quit();
}











