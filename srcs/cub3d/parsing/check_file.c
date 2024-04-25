/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:08:42 by mvpee             #+#    #+#             */
/*   Updated: 2024/04/25 11:18:19 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// typedef struct s_data
// {
//     char *north;
//     char *south;
//     char *west;
//     char *east;

//     int *floor;
//     int *ceiling;

//     char **file;
//     char **map;
// }   t_data;

bool check_file(t_data *data)
{
    int i;

    i = -1;
    while (data->file[++i])
    {
        ft_printf("%d\t%s\n", i, data->file[i]);
    }
    ft_printf("%d\n", i);
    return (false);
}
