/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:37:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/16 20:16:23 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool	check_row(char **map, int y, int x, int *count)
{
	if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != ' ' \
			&& !ft_ischarin(map[y][x], "NSWE") && !ft_isspace(map[y][x]))
		return (ft_printf_fd(2, RED INVALID_MAP RESET, y, x, map[y][x]), true);
	if (y == 0 && (map[y][x] == '0' || ft_ischarin(map[y][x], "NSWE")))
		return (ft_printf_fd(2, RED INVALID_BORDER RESET), true);
	else if (y == ft_splitlen((const char **)map) - 1 && (map[y][x] == '0' \
			|| ft_ischarin(map[y][x], "NSWE")))
		return (ft_printf_fd(2, RED INVALID_BORDER RESET), true);
	else if (map[y][x] == '0' || ft_ischarin(map[y][x], "NSWE"))
	{
		if (x == 0)
			return (ft_printf_fd(2, RED INVALID_BORDER RESET), true);
		if (ft_isspace(map[y - 1][x]) || ft_isspace(map[y][x - 1])
			|| ft_isspace(map[y + 1][x]) || ft_isspace(map[y][x + 1]))
			return (ft_printf_fd(2, RED INVALID_BORDER RESET), true);
	}
	if (ft_ischarin(map[y][x], "NSWE"))
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
		return (ft_printf_fd(2, RED WRONG_PLAYER_COUNT RESET), true);
	else if (count > 1)
		return (ft_printf_fd(2, RED WRONG_PLAYER_COUNT RESET), true);
	map_optimization(map);
	return (false);
}
