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
# include <math.h>

typedef mlx_image_t     t_img;
typedef mlx_key_data_t  t_mlx_key;

typedef enum e_move
{
    GO_RIGHT,
    GO_LEFT,
    GO_UP,
    GO_DOWN,
    ROTATE_LEFT,
    ROTATE_RIGHT
}   t_move;

typedef struct s_pos
{
    double  x;
    double  y;
}    t_pos;

typedef struct s_player_pos
{
    double  x;
    double  y;
    int     angle;
}   t_player_pos;

typedef struct s_data
{
    t_img *north_image;
    t_img *south_image;
    t_img *west_image;
    t_img *east_image;

    int     floor_color;
    int     ceiling_color;

    char    **file;
    char    **map;

    size_t        map_width;
    size_t        map_height;

    char wall_dir;

    mlx_t   *mlx;

    t_img *floor_image;
    t_img *ceiling_image;
    t_img *image;

    t_player_pos *player;
}   t_data;

// PARSING
bool    check_extension(char *str);
bool    check_file(t_data *data);
bool	check_map(char ***map);
void    map_optimization(char ***map);

// GRAPHICS
int     game_loop(t_data *data);
// KEY_HOOKS
void    move_keyhook(mlx_key_data_t keydata, void *param);
// UTILS
bool    error_handler(char *str);
int     get_rgba(int r, int g, int b, int a);
void	get_player_pos(t_data *data);
void	get_map_size(t_data *data);
bool	contain_player(char c);
char	return_element(char **map, int x, int y);
int	    get_correct_color(u_int8_t *pixel);

// RAYCASTING
float   calculate_distance_to_wall(t_data *data, float rotation, float *hitX, float *hitY);
void    draw_rays(t_data *data);

#endif
