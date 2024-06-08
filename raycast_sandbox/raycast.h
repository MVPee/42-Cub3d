#ifndef RAYCAST_H
# define RAYCAST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <MLX42/MLX42.h>
#include <string.h>
#include <float.h>
#include "../srcs/libft/includes/libft.h"

#define WIDTH 1080
#define HEIGHT 720

#define PIXEL 128
#define SPEED 32
#define SPEED_ROTATION 15
#define DEGREE 0.0833333333333333

#define mapX 5
#define mapY 5
#define mapS 25

#define RADIANT 0.0174533

#define FOV 90

// COLOR
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define BLUE    "\x1b[34m"
# define BLACK   "\x1b[30m"
# define WHITE   "\x1b[37m"
# define PINK    "\x1b[35m"
# define YELLOW  "\x1b[33m"
# define BROWN   "\x1b[33m"
# define ORANGE  "\x1b[33m"
# define PURPLE  "\x1b[35m"
# define GRAY    "\x1b[90m"
# define LIGHTGRAY "\x1b[37m"
# define DARKGRAY  "\x1b[90m"
# define RESET   "\x1b[0m"

typedef struct s_player
{
    float posX;
    float posY;
    int rotation;
}   t_player;

typedef struct s_data
{
    t_player *player;

    int red;
    int blue;
    int green;
    int pink;
    char wall_dir;
    
    mlx_image_t *floor;
    mlx_image_t *ceiling;

    mlx_t* mlx;
    mlx_image_t *img[WIDTH];
}   t_data;

#endif