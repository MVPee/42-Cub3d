/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:32 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/06 14:33:54 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// MACROS
# define PROGRAM_NAME "CUB3D"

// ERROR
# define WIN_INIT_FAILED "Windows initialization failed, check MLX"

// RESOLUTION
# define WIDTH 1280
# define HEIGHT 720

// LINUX_KEYS
# ifdef __linux__
#  define MLX_KEY_Z 87
#  define MLX_KEY_S 83
#  define MLX_KEY_Q 65
#  define MLX_KEY_D 68
# endif
// Need to find out keycode with MLX42
# ifdef __APPLE_
#  define Z_KEY 87
#  define S_KEY 83
#  define Q_KEY 65
#  define D_KEY 68
# endif 

#endif