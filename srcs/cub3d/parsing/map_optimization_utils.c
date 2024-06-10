/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_optimization_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:03:24 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/10 19:58:13 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	get_all_directions(char **map, bool *flag,int *val, char p)
{
	if (map[val[1] - 1][val[0]] == '0')
	{
		map[val[1] - 1][val[0]] = p;
		*flag = true;
	}
	if (map[val[1] + 1][val[0]] == '0')
	{
		map[val[1] + 1][val[0]] = p;
		*flag = true;
	}
	if (map[val[1]][val[0]- 1] == '0')
	{
		map[val[1]][val[0] - 1] = p;
		*flag = true;
	}
	if (map[val[1]][val[0] + 1] == '0')
	{
		map[val[1]][val[0] + 1] = p;
		*flag = true;
	}
}

void	get_all_possible_paths(char **map, char *p)
{
	int		y;
	int		x;
	bool	flag;
	int		val[2];

	flag = true;
	while (flag)
	{
		flag = false;
		y = -1;
		while (map[++y])
		{
			x = -1;
			while (map[y][++x])
			{
				if (contain_player(map[y][x]))
				{
					*p = return_element(map, x, y);
					val[0] = x;
					val[1] = y;
					get_all_directions(map, &flag, val,*p);
				}
			}		
		}
	}
}
void	get_new_map(char **map, int *n, char p)
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
			if (contain_player(map[y][x]))
				map[y][x] = '0';
		}
	}
	map[n[0]][n[1]] = p;
}

void	put_border(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0' || contain_player(map[y][x]))
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

void fetch_player_pos(char ***map, int *n)
{
	int x;
	int y;
	
	y = -1;
	while ((*map)[++y])
	{
		x = -1;
		while ((*map)[y][++x])
		{
			if (contain_player((*map)[y][x]))
			{
				n[0] = y;
				n[1] = x;
			}
		}
	}
}