/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:32 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/07 16:57:03 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// MACROS
# define PROGRAM_NAME "CUB3D"

// ERROR
# define WIN_INIT_FAILED "Windows initialization failed, check MLX"

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
# define MOVE_DISANCE 0.25

// RESOLUTION
# define WIDTH 1280
# define HEIGHT 720

// LINUX_KEYS
# ifdef __linux__
#  define MLX_KEY_Z 87
#  define MLX_KEY_S 83
#  define MLX_KEY_Q 65
#  define MLX_KEY_D 68
#  define MLX_KEY_RIGHT 263
#  define MLX_KEY_LEFT 262
# endif
// Need to find out keycode with MLX42
# ifdef __APPLE_
#  define Z_KEY 87
#  define S_KEY 83
#  define Q_KEY 65
#  define D_KEY 68
# endif 

#endif