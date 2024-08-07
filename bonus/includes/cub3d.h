/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:57:05 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/07/05 12:57:05 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"
# include "macros.h"
# include <errno.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef mlx_image_t		t_img;
typedef mlx_key_data_t	t_mlx_key;

typedef enum e_move
{
	GO_RIGHT,
	GO_LEFT,
	GO_UP,
	GO_DOWN,
	ROTATE_LEFT,
	ROTATE_RIGHT
}	t_move;

typedef struct s_player_pos
{
	double	x;
	double	y;
	int		angle;
}	t_player_pos;

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
}	t_distance;

typedef struct s_raycast
{
	float		distance;
	float		rotation;
	float		wall_height;
	int			texture_x;
	int			texture_y;
	float		hit_x;
	float		hit_y;
	float		hit_pos;
	int			color;
	int			x;
	int			y;
	mlx_image_t	*wall_img;
}	t_raycast;

typedef struct s_minimap
{
	t_img	*image;
	int		**map_input;
	int		**map_output;
	int		black;
	int		white;
	int		transparent;
	int		transparent_black;
	int		transparent_white;
	int		door;
	int		x_adjust;
	int		y_adjust;
	int		map_x;
	int		map_y;
}	t_minimap;

typedef struct s_data
{
	mlx_t			*mlx;
	t_img			*north_image;
	t_img			*south_image;
	t_img			*west_image;
	t_img			*east_image;
	t_img			*door_image;
	t_img			*image;
	t_img			*weapon_img;
	t_img			**weapon;
	int				floor_color;
	int				ceiling_color;
	char			**file;
	char			**map;
	size_t			map_width;
	size_t			map_height;
	char			wall_dir;
	t_player_pos	*player;
	t_minimap		*minimap;
	bool			*keys;
	bool			door;
}	t_data;

// PARSING
bool	check_extension(char *str);
bool	check_file(t_data *data);
bool	check_map(char ***map);

// GRAPHICS
int		game_loop(t_data *data);

// KEY_HOOKS
void	move_keyhook(void *param);

// UTILS
int		get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int		get_rgba_transparency(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void	get_player_pos(t_data *data);
void	get_map_size(t_data *data);
int		get_correct_color(u_int8_t *pixel);
void	play_sound(const char *srcs);
void	is_wall(t_data *data, float x, float y);
char	*get_weapon_path(int i);

// RAYCASTING
void	raycasting(t_data *data);

// MINIMAP
void	minimap(t_data *data);
bool	is_in_circle(int x, int y);
void	draw_square(t_minimap *minimap, int x, int y, char c);
void	get_adjust_coord(t_data *data);
void	adjust_rotated_image(t_minimap *minimap);

// RAYCASTING UTILS
float	get_distance(t_data *data, float rotation, float *hit_x, float *hit_y);

// DOOR
void	door(t_data *data);

// GUN
void	gun(t_data *data);

// INIT AND UNIT
bool	init_data(t_data *data);
void	free_data(t_data *data);
#endif
