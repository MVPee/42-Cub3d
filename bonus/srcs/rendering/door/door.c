/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:39:12 by mvpee             #+#    #+#             */
/*   Updated: 2024/07/02 20:39:50 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	close_door(t_data *data, int *pos)
{
	int	y;
	int	x;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == 'O')
			{
				data->map[y][x] = 'D';
				if (y == pos[0] && x == pos[1])
					data->map[y][x] = 'O';
				if (y + 1 == pos[0] && x == pos[1])
					data->map[y][x] = 'O';
				if (y - 1 == pos[0] && x == pos[1])
					data->map[y][x] = 'O';
				if (y == pos[0] && x + 1 == pos[1])
					data->map[y][x] = 'O';
				if (y == pos[0] && x - 1 == pos[1])
					data->map[y][x] = 'O';
			}
		}
	}
}

static void	open_door(t_data *data, int *pos)
{
	if (pos[0] > 0 && pos[0] < (int)data->map_height && pos[1] > 0
		&& pos[1] < (int)data->map_width)
	{
		if (data->map[pos[0] + 1][pos[1]] == 'D')
		{
			data->map[pos[0] + 1][pos[1]] = 'O';
			play_sound("rsrcs/sounds/door.mp3");
		}
		if (data->map[pos[0] - 1][pos[1]] == 'D')
		{
			data->map[pos[0] - 1][pos[1]] = 'O';
			play_sound("rsrcs/sounds/door.mp3");
		}
		if (data->map[pos[0]][pos[1] + 1] == 'D')
		{
			data->map[pos[0]][pos[1] + 1] = 'O';
			play_sound("rsrcs/sounds/door.mp3");
		}
		if (data->map[pos[0]][pos[1] - 1] == 'D')
		{
			data->map[pos[0]][pos[1] - 1] = 'O';
			play_sound("rsrcs/sounds/door.mp3");
		}
	}
}

void	door(t_data *data)
{
	int	y;
	int	x;
	int	pos[2];

	pos[0] = (int)data->player->y / PIXEL;
	pos[1] = (int)data->player->x / PIXEL;
	close_door(data, pos);
	open_door(data, pos);
}
