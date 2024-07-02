/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:37:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/07/02 20:39:44 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	check_row(char **map, int y, int x, int *count)
{
	if (!ft_ischarin(map[y][x], "NSWED10 ") && !ft_isspace(map[y][x]))
		return (ft_printf_fd(2, RED INVALID_MAP RESET, y, x, map[y][x]), true);
	if ((y == 0 || x == 0) && ft_ischarin(map[y][x], "NSWED0"))
		return (ft_printf_fd(2, RED INVALID_BORDER RESET), true);
	else if (y == ((int)(ft_splitlen((const char **)map)) - 1) && (ft_ischarin(map[y][x], "NSWED0")))
		return (ft_printf_fd(2, GREEN INVALID_BORDER RESET), true);
	else if (ft_ischarin(map[y][x], "NSWED0"))
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

static bool	alloc_new_map(char ***map, char ***new_map)
{
	int	y;
	int	x;

	y = -1;
	x = 0;
	while ((*map)[++y])
	{
		if ((int)ft_strlen((*map)[y]) > x)
			x = ft_strlen((*map)[y]);
	}
	(*new_map) = malloc(sizeof(char *) * (y + 1));
	if (!(*new_map))
		return (true);
	(*new_map)[y] = NULL;
	y = -1;
	while ((*map)[++y])
	{
		(*new_map)[y] = malloc(sizeof(char) * (x + 1));
		if (!(*new_map)[y])
			return (ft_free_matrix(1, new_map), true);
		(*new_map)[y][x] = '\0';
		ft_memset((*new_map)[y], '1', x);
	}
	return (false);
}

static bool	get_new_map(char ***map)
{
	int		x;
	int		y;
	char	**new_map;

	if (alloc_new_map(map, &new_map))
		return (true);
	y = -1;
	while ((*map)[++y])
	{
		x = -1;
		while ((*map)[y][++x])
			if ((*map)[y][x] == '0' || ft_ischarin((*map)[y][x], "NSWED"))
				new_map[y][x] = (*map)[y][x];
	}
	ft_free_matrix(1, map);
	*map = ft_splitdup((const char **)new_map);
	if (!*map)
		return (ft_free_matrix(1, &new_map), true);
	return (ft_free_matrix(1, &new_map), false);
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
	if (count != 1)
		return (ft_printf_fd(2, RED WRONG_PLAYER_COUNT RESET), true);
	if (get_new_map(map))
		return (true);
	return (false);
}
