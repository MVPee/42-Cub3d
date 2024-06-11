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

typedef struct s_player_pos
{
    double  x;
    double  y;
    int     angle;
}   t_player_pos;

// RAYCAST STRUCTURES

typedef struct s_distance
{
    float	x;
    float	y;
    float	angle_rad;
    float	step_x;
    float	step_y;
    int		prev_x;
    int		prev_y;
	float	distance;
}   t_distance;

typedef t_distance t_dist;

typedef struct s_raycast
{
    float		distance;
    float		rotation;
    float		wall_height;
    int			texture_x;
	int			texture_y;
    float		hitX;
	float		hitY;
    float		hitPos;
    int			color;
    int			x;
	int			y;
	mlx_image_t	*wall_img;
}   t_raycast;

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
    t_img *fog;
    t_img *image;
    t_img *minimap;
    t_img *arrow;
    t_player_pos *player;
}   t_data;

// PARSING
bool    check_extension(char *str);
bool    check_file(t_data *data);
bool	check_map(char ***map);
void    map_optimization(char ***map);
void    fetch_player_pos(char ***map, int *n);
void	put_border(char **map);
void	get_new_map(char **map, int *n, char p);
void	get_all_possible_paths(char **map, char *p);
// PARSING UTILS
void	get_all_directions(char **map, bool *flag,int *val, char p);
void	get_all_possible_paths(char **map, char *p);
void	get_new_map(char **map, int *n, char p);
void	put_border(char **map);
void    fetch_player_pos(char ***map, int *n);
// GRAPHICS
int     game_loop(t_data *data);
// KEY_HOOKS
void    move_keyhook(mlx_key_data_t keydata, void *param);
// UTILS
bool    error_handler(char *str);
int     get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void	get_player_pos(t_data *data);
void	get_map_size(t_data *data);
bool	contain_player(char c);
char	return_element(char **map, int x, int y);
int	    get_correct_color(u_int8_t *pixel);

// RAYCASTING
void    draw_rays(t_data *data);
void    mini_map(t_data *data);
// RAYCASTING UTILS
float get_distance(t_data *data, float rotation, float *hitX, float *hitY);

// INIT AND UNIT
bool init_data(t_data *data);
void free_data(t_data *data);
#endif
