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

typedef mlx_image_t img_t;

typedef struct s_data
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;

    int     *floor;
    int     *ceiling;

    char    **file;
    char    **map;

    mlx_t   *mlx;
    img_t   *image;
}   t_data;

typedef struct s_pos
{
	double	x;
	double  y;
}	t_pos;

// PARSING
bool    check_extension(char *str);
bool    check_file(t_data *data);
bool    check_map(char **map);

// GRAPHICS
int game_loop(t_data *data);
// KEY_HOOKS
void move_keyhook(mlx_key_data_t keydata, void *param);
// UTILS
bool    error_handler(char *str);


#endif
