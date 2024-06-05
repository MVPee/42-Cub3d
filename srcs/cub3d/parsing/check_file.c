/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:08:42 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/05 09:19:08 by mvpee            ###   ########.fr       */
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
    char *temp;
    char **split;

    i = -1;
    while (data->file[++i])
    {
        if (!ft_strncmp(data->file[i], "NO ", 3))
            data->north = ft_substr(data->file[i], 3, ft_strlen(data->file[i]) - 4);
        else if (!ft_strncmp(data->file[i], "SO ", 3))
            data->south = ft_substr(data->file[i], 3, ft_strlen(data->file[i]) - 4);
        else if (!ft_strncmp(data->file[i], "WE ", 3))
            data->west = ft_substr(data->file[i], 3, ft_strlen(data->file[i]) - 4);
        else if (!ft_strncmp(data->file[i], "EA ", 3))
            data->east = ft_substr(data->file[i], 3, ft_strlen(data->file[i]) - 4);
        else if (!ft_strncmp(data->file[i], "F ", 2))
        {
            temp = ft_substr(data->file[i], 2, ft_strlen(data->file[i]) - 3);
            if (!temp)
                return (true);
            split = ft_split(temp, ", ");
            if (!split)
                return (ft_free(1, &temp), true);
            data->floor[0] = ft_atoi(split[0]);
            data->floor[1] = ft_atoi(split[1]);
            data->floor[2] = ft_atoi(split[2]);
            ft_free(1, &temp);
            ft_free_matrix(1, &split);
        }
        else if (!ft_strncmp(data->file[i], "C ", 2))
        {
            temp = ft_substr(data->file[i], 2, ft_strlen(data->file[i]) - 3);
            if (!temp)
                return (true);
            split = ft_split(temp, ", ");
            if (!split)
                return (ft_free(1, &temp), true);
            data->ceiling[0] = ft_atoi(split[0]);
            data->ceiling[1] = ft_atoi(split[1]);
            data->ceiling[2] = ft_atoi(split[2]);
            ft_free(1, &temp);
            ft_free_matrix(1, &split);
        }
        else
            data->map = ft_splitjoin(data->map, data->file[i]);
    }
    if (!data->north || !data->south || !data->west || !data->east)
        return (true);
    return (false);
}
