/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:36:30 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/10 19:15:39 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (255 << 24 | b << 16 | g << 8 | r);
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

bool	error_handler(char *str)
{
	if (!str)
		return (false);
	ft_printf_fd(STDERR_FILENO, "%s\n", str);
	return (false);
	}

bool	contain_player(char c)
{
	char	charset[4];
	size_t	index;

	index = 0;
	charset[0] = 'N';
	charset[1] = 'S';
	charset[2] = 'W';
	charset[3] = 'E';
	while (index < 4)
	{
		if (c == charset[index])
			return (true);
		index++;
	}
	return false;
}

char	return_element(char **map, int x, int y)
{
	return (map[y][x]);
}

void	set_cardinal_dir(t_data *data, int x, int y)
{
	char c;

	if (!data)
		return ;
	c = data->map[y][x];
	if (c == 'N')
		data->player->angle = 270;
	else if (c == 'E')
		data->player->angle = 0;
	else if (c == 'S')
		data->player->angle = 90;
	else if (c == 'W')
		data->player->angle = 180;
}

void	get_player_pos(t_data *data)
{
	int		x;
	int		y;
	
	x = -1;
	while (++x < data->map_width)
	{
		y = -1;
		while (++y < data->map_height)
		{
			if (contain_player(data->map[y][x]))
			{
				data->player->x = x * PIXEL + ((float) PIXEL / 2);
				data->player->y = y * PIXEL + ((float) PIXEL / 2);
				set_cardinal_dir(data, x, y);
				break;
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