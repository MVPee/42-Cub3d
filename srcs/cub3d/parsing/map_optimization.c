/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_optimization.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:54:33 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/09 21:29:27 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	get_all_directions(char **map, bool *flag, int y, int x, char p)
{
	if (map[y - 1][x] == '0')
	{
		map[y - 1][x] = p;
		*flag = true;
	}
	if (map[y + 1][x] == '0')
	{
		map[y + 1][x] = p;
		*flag = true;
	}
	if (map[y][x - 1] == '0')
	{
		map[y][x - 1] = p;
		*flag = true;
	}
	if (map[y][x + 1] == '0')
	{
		map[y][x + 1] = p;
		*flag = true;
	}
}

static void	get_all_possible_paths(char **map, char *p)
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
			{
				if (contain_player(map[y][x]))
				{
					*p = return_element(map, x, y);
					get_all_directions(map, &flag, y, x, *p);
				}
			}		
		}
	}
}

static void	get_new_map(char **map, int *n, char p)
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

void map_optimization(char ***map)
{
	int	n[2];
	int	y;
	int	x;
	char p;

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
	get_all_possible_paths(*map, &p);
	get_new_map(*map, n, p);
	put_border(*map);

	y = 0;
	x = 0;
	int min = INT_MAX;
	int max = INT_MIN;
	for (int i = 0; i < ft_splitlen((const char **)*map); i++)
		if (ft_ischarin('1', (*map)[i]))
			y++;

	for (int i = 0; i < ft_splitlen((const char **)*map); i++)
	{
		for (int j = 0; j < ft_strlen((*map)[i]); j++)
		{
			if ((*map)[i][j] == '1')
			{
				if (min > j)
					min = j;
				if (max < j)
					max = j;
			}
		}
	}

	x = max + 1 - min;
	char **new_map = (char **)malloc(sizeof(char *) * (y + 1));
	for (int i = 0; i < y; i++)
	{
		new_map[i] = (char *)malloc(sizeof(char) * (x + 1));
		new_map[i][x] = '\0';
	}
	new_map[y] = NULL;

	int start = 0;

	for (int i = 0; i < ft_splitlen((const char **)*map); i++)
	{
		if (ft_ischarin('1', (*map)[i]))
		{
			start = i;
			break;
		}
	}

    for (int i = 0; i < y; i++) {
        int old_row_length = ft_strlen((*map)[i + start]);
        for (int j = 0; j < x; j++) {
            if (j + min < old_row_length) {
                new_map[i][j] = (*map)[i + start][j + min];
            } else {
                new_map[i][j] = ' ';
            }
        }
    }

	ft_free_matrix(1, map);
	*map = ft_splitdup((const char **)new_map);
	ft_free_matrix(1, &new_map);
}
