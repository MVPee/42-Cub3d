/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_optimization.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:54:33 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/06 14:56:52 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"


static void	get_all_directions(char **map, bool *flag, int y, int x)
{
	if (map[y - 1][x] == '0')
	{
		map[y - 1][x] = 'N';
		*flag = true;
	}
	if (map[y + 1][x] == '0')
	{
		map[y + 1][x] = 'N';
		*flag = true;
	}
	if (map[y][x - 1] == '0')
	{
		map[y][x - 1] = 'N';
		*flag = true;
	}
	if (map[y][x + 1] == '0')
	{
		map[y][x + 1] = 'N';
		*flag = true;
	}
}

static void	get_all_possible_paths(char **map)
{
	int		y;
	int		x;
	bool	flag;

	flag = true;
	while (flag)
	{
		flag = false;
		y = -1;
		while (map[++y])
		{
			x = -1;
			while (map[y][++x])
				if (map[y][x] == 'N')
					get_all_directions(map, &flag, y, x);
		}
	}
}

static void	get_new_map(char **map, int *n)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0' || map[y][x] == '1')
				map[y][x] = ' ';
		}
	}
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N')
				map[y][x] = '0';
		}
	}
	map[n[0]][n[1]] = 'N';
}

static void	put_border(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0')
			{
				if (map[y - 1][x] == ' ')
					map[y - 1][x] = '1';
				if (map[y + 1][x] == ' ')
					map[y + 1][x] = '1';
				if (map[y][x - 1] == ' ')
					map[y][x - 1] = '1';
				if (map[y][x + 1] == ' ')
					map[y][x + 1] = '1';
			}
		}
	}
}

void	map_optimization(char **map)
{
	int	n[2];
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N')
			{
				n[0] = y;
				n[1] = x;
			}
		}
	}
	get_all_possible_paths(map);
	get_new_map(map, n);
	put_border(map);
}
