/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:18:10 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/06 11:18:10 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../srcs/libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "macros.h"
# include <stdio.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <limits.h>
#define BPP 4

typedef mlx_image_t img_t;

typedef struct s_data
{
    img_t *north_image;
    img_t *south_image;
    img_t *west_image;
    img_t *east_image;

    int     floor_color;
    int     ceiling_color;

    char    **file;
    char    **map;

    mlx_t   *mlx;

    img_t *floor_image;
    img_t *ceiling_image;
}   t_data;

typedef struct s_pos
{
	double	x;
	double  y;
}	t_pos;

// PARSING
bool    check_extension(char *str);
bool    check_file(t_data *data);
bool	check_map(char ***map);
void    map_optimization(char ***map);

// GRAPHICS
int game_loop(t_data *data);
// KEY_HOOKS
void move_keyhook(mlx_key_data_t keydata, void *param);
// UTILS
bool    error_handler(char *str);
int get_rgba(int r, int g, int b, int a);


#endif
