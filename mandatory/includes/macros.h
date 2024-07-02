/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:32 by nechaara          #+#    #+#             */
/*   Updated: 2024/07/02 20:59:18 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// MACROS
# define PROGRAM_NAME "CUB3D"

// ERROR
# define WIN_INIT_FAILED "Windows initialization failed, check MLX\n"
# define INVALID_MAP "Error\nInvalid map in y: %d x:%d c:'%c'\n"
# define INVALID_BORDER "Error\nBad Border\n"
# define WRONG_PLAYER_COUNT "Error\nWrong player count\n"
# define NUMBERS_OF_ARGUMENTS "Error\nNumber of argument(s)\n"
# define FLOOR_COLOR "Error\nBad floor color\n"
# define CEILING_COLOR "Error\nBad ceiling color\n"

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

// MOVEMENT MACROS
# define RADIANT 0.0174533
# define PIXEL 128
# define SPEED 8
# define SPEED_ROTATION 5
# define DEGREE 0.0833333333333333
# define FOV 60
# define F_PI 57.2957795131

// RESOLUTION
# define WIDTH 1080
# define HEIGHT 720

// MINIMAP
# define MINIMAP_SIZE 200
# define WALL_SIZE 20
# define PLAYER_SIZE 10

// KEY
# define MLX_KEY_Z 87
# define MLX_KEY_S 83
# define MLX_KEY_Q 65
# define MLX_KEY_D 68
# define MLX_KEY_RIGHT 262
# define MLX_KEY_LEFT 263
# define MLX_KEY_ESCAPE 256
# define MLX_KEY_SHIFT 340

#endif