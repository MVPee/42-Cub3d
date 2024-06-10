/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:37:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/10 15:57:39 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool	check_row(char **map, int y, int x, int *count)
{
	if ((map[y][x] != '1' && map[y][x] != '0' && map[y][x] != ' ' \
			&& !contain_player(map[y][x])) && !ft_isspace(map[y][x]))
		return (ft_printf_fd(2, RED INVALID_MAP RESET, y, x, map[y][x]), true);
	if (y == 0 && (map[y][x] == '0' || contain_player(map[y][x])))
		return (ft_printf_fd(2, RED INVALID_BORDER RESET), true);
	else if (y == ft_splitlen((const char **)map) - 1 && (map[y][x] == '0' \
			|| contain_player(map[y][x])))
		return (ft_printf_fd(2, RED INVALID_BORDER RESET), true);
	else if (map[y][x] == '0' || contain_player(map[y][x]))
	{
		if (x == 0)
			return (ft_printf_fd(2, RED INVALID_BORDER RESET), true);
		if (ft_isspace(map[y - 1][x]) || ft_isspace(map[y][x - 1])
			|| ft_isspace(map[y + 1][x]) || ft_isspace(map[y][x + 1]))
			return (ft_printf_fd(2, RED INVALID_BORDER RESET), true);
	}
	if (contain_player(map[y][x]))
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
