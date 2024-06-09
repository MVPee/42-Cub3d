/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:32 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/09 15:08:06 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// MACROS
# define PROGRAM_NAME "CUB3D"

// ERROR
# define WIN_INIT_FAILED "Windows initialization failed, check MLX"
# define INVALID_MAP "Error\nInvalid map in y: %d x:%d c:'%c'\n"
# define INVALID_BORDER "Error\nBad Border\n"
# define WRONG_PLAYER_COUNT "Error\nWrong player count\n"
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
# define RADIANT 0.0174533 //per 1 degree
# define PIXEL 128
# define SPEED 32
# define SPEED_ROTATION 15
# define DEGREE 0.0833333333333333 // beetween ray (POV/WIDTH)
# define FOV 90

// RESOLUTION
# define WIDTH 1080
# define HEIGHT 720

// LINUX_KEYS
# ifdef __linux__
#  define MLX_KEY_Z 87
#  define MLX_KEY_S 83
#  define MLX_KEY_Q 65
#  define MLX_KEY_D 68
#  define MLX_KEY_RIGHT 262
#  define MLX_KEY_LEFT 263
# endif
// Need to find out keycode with MLX42
# ifdef __APPLE_
#  define Z_KEY 87
#  define S_KEY 83
#  define Q_KEY 65
#  define D_KEY 68
# endif 

#endif