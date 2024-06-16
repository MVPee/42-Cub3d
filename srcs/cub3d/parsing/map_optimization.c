/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_optimization.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:54:33 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/16 20:18:10 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	set_min_max(int *x, int *y, char ***map, int *min, int *max)
{
	int	i;
	int	j;

	i = -1;
	while (++i < ft_splitlen((const char **)*map))
		if (ft_ischarin('1', (*map)[i]))
			*y = *y + 1;
	i = -1;
	while (++i < ft_splitlen((const char **)*map))
	{
		j = -1;
		while (++j < ft_strlen((*map)[i]))
		{
			if ((*map)[i][j] == '1')
			{
				if (*min > j)
					*min = j;
				if (*max < j)
					*max = j;
			}
		}
	}
	*x = *max + 1 - *min;
}

static void	populate_new_map(char ***map, char **new_map, int start, int x,
		int y, int min)
{
	int	i;
	int	j;
	int	old_row_length;

	i = -1;
	while (++i < y)
	{
		old_row_length = ft_strlen((*map)[i + start]);
		j = -1;
		while (++j < x)
		{
			if (j + min < old_row_length)
				new_map[i][j] = (*map)[i + start][j + min];
			else
				new_map[i][j] = '1';
		}
	}
	ft_free_matrix(1, map);
	*map = ft_splitdup((const char **)new_map);
	ft_free_matrix(1, &new_map);
}

static void	generate_new_map(char ***map, int *x, int *y, int *min, int *max)
{
	char	**new_map;
	int		start;
	int		i;

	new_map = (char **)malloc(sizeof(char *) * (*y + 1));
	i = -1;
	while (++i < *y)
	{
		new_map[i] = (char *)malloc(sizeof(char) * (*x + 1));
		new_map[i][*x] = '\0';
	}
	new_map[*y] = NULL;
	start = 0;
	i = -1;
	while (++i < ft_splitlen((const char **)*map))
	{
		if (ft_ischarin('1', (*map)[i]))
		{
			start = i;
			break ;
		}
	}
	populate_new_map(map, new_map, start, *x, *y, *min);
}

static void	fill_void_spaces_map(char **map)
{
	for (int i = 0; i < ft_splitlen((const char **)map); i++)
	{
		for (int j = 0; j < ft_strlen(map[i]); j++)
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
		}
	}
}

void	map_optimization(char ***map)
{
	int		n[2];
	int		min_max[2];
	int		y;
	int		x;
	char	p;
	int		min;
	int		max;

	y = 0;
	x = 0;
	min = INT_MAX;
	max = INT_MIN;
	fetch_player_pos(map, n);
	get_all_possible_paths(*map, &p);
	get_new_map(*map, n, p);
	put_border(*map);
	set_min_max(&x, &y, map, &min, &max);
	generate_new_map(map, &x, &y, &min, &max);
	fill_void_spaces_map(*map);
}
