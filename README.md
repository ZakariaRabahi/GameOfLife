## [Game of Life](https://github.com/yourusername/GameOfLife)

This project is an implementation of Conway's **Game of Life**, developed in **C**. It simulates a zero-player game in which the evolution of cells is determined by initial configurations. This particular project uses **SDL2** for rendering, making it possible to visually represent the simulation of cellular automaton on a grid.

### Features:
- The simulation follows Conway's Game of Life rules to create complex patterns from simple initial conditions.
- It supports reading and saving grid configurations for continuity in simulation, as demonstrated by the `Saved_Matrix.txt` file.
- Efficient use of **SDL2** for graphical display of the evolving matrix.

### Technologies Used:
- **C**: Core game logic, focusing on performance and efficient memory handling.
- **SDL2**: Used for rendering the grid and visualizing the simulation in real time.
- **Makefile**: For compiling the project and managing dependencies easily.
- **CMake**: Employed to handle the build process, ensuring compatibility across different systems and environments.

### Key Files:
- `main.c`: Contains the main program logic for the Game of Life simulation.
- `make_matrix.c` & `make_matrix.h`: Functions for creating and managing the matrix of cells used in the game.
- `Saved_Matrix.txt`: A file used to store and load previously saved game configurations.

### Key Learning Outcomes:
- Gained hands-on experience with low-level programming in **C** for a simulation-based project.
- Developed proficiency in using **SDL2** for graphical rendering in C applications.
- Learned how to work with **CMake** and **Makefile** to automate the build process for larger C projects.
- Improved understanding of memory management, file I/O, and game loop mechanics.

You can view the project on GitHub: [Game of Life](https://github.com/ZakariaRabahi/GameOfLife)
