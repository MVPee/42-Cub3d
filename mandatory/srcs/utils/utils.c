/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:36:30 by nechaara          #+#    #+#             */
/*   Updated: 2024/07/02 21:32:28 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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

bool	check_extension(char *str)
{
	char	*temp;

	temp = ft_substr(str, ft_strlen(str) - 4, ft_strlen(str));
	if (!temp)
		return (perror("Malloc"), true);
	if (ft_strlen(str) < 5 || ft_strcmp(temp, ".cub"))
		return (ft_free(1, &temp), ft_printf_fd(2,
				RED "Error\nInvalid map extension\n" RESET), true);
	ft_free(1, &temp);
	return (false);
}
