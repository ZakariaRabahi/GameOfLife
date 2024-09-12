//
// Created by zk on 16/12/22.
//

#ifndef GAMEOFLIFE_PREPROJECT_MAKE_MATRIX_H
#define GAMEOFLIFE_PREPROJECT_MAKE_MATRIX_H
#include <stdio.h>
#include <stdlib.h>

/*
 * Importeert de nodige functies uit SDL2.
 */
#include <SDL2/SDL.h>

/*
 * Op moderne OSX systemen moet voor Retina displays expliciet de dimensies van getekende figuren verdubbeld worden,
 * aangezien die een hogere dpi hebben.
 * Op andere besturingssystemen moet dat niet gebeuren.
 */
#ifdef __MAC_10_15
#define DPI_SCALING 2
#else
#define DPI_SCALING 1
#endif

static SDL_Renderer *renderer;
static SDL_Window *window;

int initialize_matrix();
void clear_window();
void draw_window();


int update_matrix();


void initialize_window();

void free_gui();
void save_matrix();
int matrix_make_zero();
int init_matrix();

#endif