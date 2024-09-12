#include "make_matrix.h"
int should_continue = 1;
void read_input() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    free_gui();
                    should_continue = 0;
            }
        }
}

int main(int argc, char *argv[]) {
    /* Initialiseert het venster */
    initialize_window("Game of Life");
    matrix_make_zero();
    init_matrix("world.txt");

    while (should_continue) {
    read_input();
    update_matrix();
    save_matrix();
    draw_window();
    SDL_Delay(150);
    read_input();
    }
    /* Dealloceert al het geheugen dat werd aangemaakt door SDL zelf. */
    return 0;
}