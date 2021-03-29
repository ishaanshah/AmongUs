#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Screen size
#define WIDTH 1920
#define HEIGHT 1080

// Number rows and columns in the maze
#define NCOLS 16
#define NROWS 9

#define FONT_SIZE 20

// Dimension of cell
#define WALL_SIZE 6

// Dimensions of character
#define CHARACTER_SIZE 54
#define CHARACTER_VELOCITY 150

// Dimensions of coin
#define COIN_SIZE 40

// Dimensions of bomb
#define BOMB_SIZE 40

// Circle resolution
#define CIRCLE_RES 20

// Time limit
#define TIME_LIMIT 120.0f

// RGB values for different colors
// TODO: Set to nord theme
#define COLOR_RED glm::vec3(1.0f, 0.0f, 0.0f)
#define COLOR_GREEN glm::vec3(0.0f, 1.0f, 0.0f)
#define COLOR_BLUE glm::vec3(0.0f, 0.0f, 1.0f)
#define COLOR_CYAN glm::vec3(0.0f, 1.0f, 1.0f)
#define COLOR_YELLOW glm::vec3(1.0f, 1.0f, 0.0f)
#define COLOR_PURPLE glm::vec3(0.5f, 0.0f, 0.5f)
#define COLOR_BLACK glm::vec3(0.0f, 0.0f, 0.0f)
#define COLOR_GREY glm::vec3(0.4f, 0.4f, 0.4f)
#define COLOR_WHITE glm::vec3(1.0f, 1.0f, 1.0f)

#endif
