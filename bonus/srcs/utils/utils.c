/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:36:30 by nechaara          #+#    #+#             */
/*   Updated: 2024/07/03 17:25:56 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	is_wall(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x / PIXEL;
	map_y = (int)y / PIXEL;
	if (map_x < 0 || map_x >= (int)data->map_width || map_y < 0
		|| map_y >= (int)data->map_height)
		return ;
	if (data->map[(int)data->player->y / PIXEL][((int)x + PIXEL / 8)
		/ PIXEL] == '1')
		x = data->player->x;
	if (data->map[((int)y + PIXEL / 8) / PIXEL][(int)data->player->x
		/ PIXEL] == '1')
		y = data->player->y;
	if (data->map[(int)data->player->y / PIXEL][((int)x - PIXEL / 8)
		/ PIXEL] == '1')
		x = data->player->x;
	if (data->map[((int)y - PIXEL / 8) / PIXEL][(int)data->player->x
		/ PIXEL] == '1')
		y = data->player->y;
	if (data->map[(int)data->player->y / PIXEL][(int)x / PIXEL] != '1')
		data->player->x = x;
	if (data->map[(int)y / PIXEL][(int)data->player->x / PIXEL] != '1')
		data->player->y = y;
}

void	get_map_size(t_data *data)
{
	int	map_width;
	int	map_height;

	map_width = ft_strlen(data->map[0]);
	map_height = ft_splitlen((const char **)data->map);
	data->map_width = map_width;
	data->map_height = map_height;
}

void	get_player_pos(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (++x < (int)data->map_width)
	{
		y = -1;
		while (++y < (int)data->map_height)
		{
			if (ft_ischarin(data->map[y][x], "NSWE"))
			{
				data->player->x = x * PIXEL + ((float)PIXEL / 2);
				data->player->y = y * PIXEL + ((float)PIXEL / 2);
				if (data->map[y][x] == 'N')
					data->player->angle = 270;
				else if (data->map[y][x] == 'E')
					data->player->angle = 0;
				else if (data->map[y][x] == 'S')
					data->player->angle = 90;
				else if (data->map[y][x] == 'W')
					data->player->angle = 180;
			}
		}
	}
}

int	get_correct_color(u_int8_t *pixel)
{
	int	rgba;

	rgba = 0;
	rgba += pixel[0] << 24;
	rgba += pixel[1] << 16;
	rgba += pixel[2] << 8;
	rgba += pixel[3];
	return (rgba);
}

void	play_sound(const char *srcs)
{
	pid_t	mpg123_pid;

	if (PLAY == 1)
	{
		mpg123_pid = fork();
		if (mpg123_pid == 0)
			execlp("mpg123", "mpg123", srcs, NULL);
	}
}
