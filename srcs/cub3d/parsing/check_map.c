/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:37:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/06 19:06:32 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool	check_row(char **map, int y, int x, int *count)
{
	if ((map[y][x] != '1' && map[y][x] != '0' && map[y][x] != ' ' \
			&& map[y][x] != 'N') && !ft_isspace(map[y][x]))
		return (ft_printf_fd(2, "Error\nInvalid map in y:%d x:%d c:'%c'\n", y, \
				x, map[y][x]), true);
	if (y == 0 && (map[y][x] == '0' || map[y][x] == 'N'))
		return (ft_printf_fd(2, "Error\nBad Border\n"), true);
	else if (y == ft_splitlen((const char **)map) - 1 && (map[y][x] == '0' \
			|| map[y][x] == 'N'))
		return (ft_printf_fd(2, "Error\nBad Border\n"), true);
	else if (map[y][x] == '0' || map[y][x] == 'N')
	{
		if (x == 0)
			return (ft_printf_fd(2, "Error\nBad Border\n"), true);
		if (ft_isspace(map[y - 1][x]) || ft_isspace(map[y][x - 1])
			|| ft_isspace(map[y + 1][x]) || ft_isspace(map[y][x + 1]))
			return (ft_printf_fd(2, "Error\nBad Border\n"), true);
	}
	if (map[y][x] == 'N')
		*count += 1;
	return (false);
}

bool	check_map(char ***map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	if (!map || !*map)
		return (true);
	y = -1;
	while ((*map)[++y])
	{
		x = -1;
		while ((*map)[y][++x])
			if (check_row(*map, y, x, &count))
				return (true);
	}
	if (count == 0)
		return (ft_printf_fd(2, "Error\nNo player online\n"), true);
	else if (count > 1)
		return (ft_printf_fd(2, "Error\nIt's not a multiplayer game\n"), true);
	map_optimization(map);
	return (false);
}
