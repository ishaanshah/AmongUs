#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Screen size
#define WIDTH 1920
#define HEIGHT 1080

// Number rows and columns in the maze
#define NCOLS 16
#define NROWS 9

// Dimension of cell
#define WALL_SIZE 6

// Dimensions of character
#define CHARACTER_SIZE 54
#define CHARACTER_VELOCITY 150

// Circle resolution
#define CIRCLE_RES 20

// RGB values for different colors
// TODO: Set to nord theme
#define COLOR_RED glm::vec3(1.0f, 0.0f, 0.0f)
#define COLOR_GREEN glm::vec3(0.0f, 1.0f, 0.0f)
#define COLOR_BLUE glm::vec3(0.0f, 0.0f, 1.0f)
#define COLOR_CYAN glm::vec3(0.0f, 1.0f, 1.0f)
#define COLOR_YELLOW glm::vec3(1.0f, 1.0f, 0.0f)
#define COLOR_BLACK glm::vec3(0.0f, 0.0f, 0.0f)
#define COLOR_WHITE glm::vec3(1.0f, 1.0f, 1.0f)

#endif
