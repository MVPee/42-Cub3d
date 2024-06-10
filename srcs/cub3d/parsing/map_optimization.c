/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_optimization.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:54:33 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/10 15:54:30 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

// TODO : Je vais refactor la fonction chef ne t'inquetes pas

void map_optimization(char ***map)
{
	int	n[2];
	int	y;
	int	x;
	char p;

	fetch_player_pos(map, n);
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