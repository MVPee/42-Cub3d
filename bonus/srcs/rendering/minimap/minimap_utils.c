/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:43:10 by mvpee             #+#    #+#             */
/*   Updated: 2024/07/02 20:39:58 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	map_init(t_data *data)
{
	int	i;
	int	j;

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
}

void	get_adjust_coord(t_data *data)
{
	data->minimap->x_adjust = -5;
	data->minimap->y_adjust = -5;
}

bool	is_in_circle(int x, int y)
{
	int	dx;
	int	dy;

	dy = y - MINIMAP_SIZE / 2;
	dx = x - MINIMAP_SIZE / 2;
	return ((dx * dx + dy * dy) < (MINIMAP_SIZE / 2) * (MINIMAP_SIZE / 2));
}

void	draw_square(t_minimap *minimap, int x, int y, char c)
{
	int	color;
	int	size;
	int	i;
	int	j;

	if (c == 'P')
	{
		color = minimap->white;
		size = PLAYER_SIZE;
	}
	else if (c == 'D')
	{
		color = minimap->door;
		size = WALL_SIZE;
	}
	else
	{
		color = minimap->transparent_white;
		size = WALL_SIZE;
	}
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			if (x + j >= 0 && x + j < MINIMAP_SIZE && y + i >= 0 && y
				+ i < MINIMAP_SIZE)
				minimap->map_input[x + j][y + i] = color;
	}
}
