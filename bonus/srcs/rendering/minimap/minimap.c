/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:46:41 by mvpee             #+#    #+#             */
/*   Updated: 2024/07/05 12:56:55 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	rotate_image(t_minimap *minimap, double cos_angle, double sin_angle)
{
	int	y;
	int	x;
	int	new_x;
	int	new_y;

	y = -1;
	while (++y < MINIMAP_SIZE)
	{
		x = -1;
		while (++x < MINIMAP_SIZE)
		{
			new_x = (int)((x - MINIMAP_SIZE / 2) * cos_angle - (y - MINIMAP_SIZE
						/ 2) * sin_angle + MINIMAP_SIZE / 2);
			new_y = (int)((x - MINIMAP_SIZE / 2) * sin_angle + (y - MINIMAP_SIZE
						/ 2) * cos_angle + MINIMAP_SIZE / 2);
			if (new_x >= 0 && new_x < MINIMAP_SIZE && new_y >= 0
				&& new_y < MINIMAP_SIZE)
				minimap->map_output[new_y][new_x] = minimap->map_input[y][x];
		}
	}
	adjust_rotated_image(minimap);
}

static void	draw_path2(t_data *data, int j, int i)
{
	t_minimap	*minimap;
	char		c;

	minimap = data->minimap;
	minimap->map_x = (int)data->player->x / PIXEL + i;
	minimap->map_y = (int)data->player->y / PIXEL + j;
	c = 'W';
	if (minimap->map_x >= 0 && minimap->map_x < (int)data->map_width
		&& minimap->map_y >= 0 && minimap->map_y < (int)data->map_height
		&& ft_ischarin(data->map[minimap->map_y][minimap->map_x],
		"NSWE0DO"))
	{
		if (ft_ischarin(data->map[minimap->map_y][minimap->map_x], "D"))
			c = 'D';
		draw_square(minimap, minimap->x_adjust + MINIMAP_SIZE / 2 + i
			* WALL_SIZE, minimap->y_adjust + MINIMAP_SIZE / 2 + j
			* WALL_SIZE, c);
	}
}

static void	draw_path(t_data *data)
{
	int			i;
	int			j;
	t_minimap	*minimap;

	minimap = data->minimap;
	i = ((MINIMAP_SIZE / 40 + 1) * -1) - 1;
	while (++i <= (MINIMAP_SIZE / 40 + 1))
	{
		j = ((MINIMAP_SIZE / 40 + 1) * -1) - 1;
		while (++j <= (MINIMAP_SIZE / 40 + 1))
			draw_path2(data, i, j);
	}
}

static void	draw_minimap(t_data *data)
{
	int	i;
	int	j;

	draw_path(data);
	draw_square(data->minimap, 5 + (MINIMAP_SIZE / 2 - PLAYER_SIZE / 2), (5
			+ MINIMAP_SIZE / 2 - PLAYER_SIZE / 2), 'P');
	rotate_image(data->minimap, cos((data->player->angle + 90) * RADIANT),
		sin((data->player->angle + 90) * RADIANT));
	i = -1;
	while (++i < MINIMAP_SIZE)
	{
		j = -1;
		while (++j < MINIMAP_SIZE)
		{
			if (!is_in_circle(j - 1, i) || !is_in_circle(j + 1, i)
				|| !is_in_circle(j, i - 1) || !is_in_circle(j, i + 1))
				mlx_put_pixel(data->minimap->image, j, i, data->minimap->black);
			if (!is_in_circle(j, i))
				mlx_put_pixel(data->minimap->image, j, i,
					data->minimap->transparent);
			else
				mlx_put_pixel(data->minimap->image, i, j,
					data->minimap->map_output[i][j]);
		}
	}
}

void	minimap(t_data *data)
{
	int	i;
	int	j;

	get_adjust_coord(data);
	i = -1;
	while (++i < MINIMAP_SIZE)
	{
		j = -1;
		while (++j < MINIMAP_SIZE)
		{
			data->minimap->map_input[i][j] = data->minimap->transparent_black;
			data->minimap->map_output[i][j] = 0;
		}
	}
	draw_minimap(data);
}
