/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:36:30 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/07 18:10:24 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include <stdbool.h>

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
			if (data->map[y][x] == 'N')
			{
				if (x == 0)
					data->player->position.x = y + 0.5;
				else
					data->player->position.x = y - 0.5;
				if (y == 0)
					data->player->position.y = x + 0.5;
				else
					data->player->position.y = x - 0.5;
				break;
			}
		}
	}
}
