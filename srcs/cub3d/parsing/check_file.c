/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:08:42 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/05 10:17:06 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void get_texture(char **texture, char *line)
{
    ft_free(1, texture);
    *texture = ft_substr(line, 3, ft_strlen(line) - 4);
}

static void get_color(int *array, char *line)
{
    char **split;
    int i;

    i = -1;
    split = ft_split(line, ", ");
    if (split)
    {
        while (++i < 3 && split[i])
            array[i] = ft_atoi(split[i]);
        ft_free_matrix(1, &split);   
    }
    ft_free(1, &line);
}

bool check_file(t_data *data)
{
    int i;
    char *temp;
    char **split;

    i = -1;
    while (data->file[++i])
    {
        if (!ft_strncmp(data->file[i], "NO ", 3))
            get_texture(&data->north, data->file[i]);
        else if (!ft_strncmp(data->file[i], "SO ", 3))
            get_texture(&data->south, data->file[i]);
        else if (!ft_strncmp(data->file[i], "WE ", 3))
            get_texture(&data->west, data->file[i]);
        else if (!ft_strncmp(data->file[i], "EA ", 3))
            get_texture(&data->east, data->file[i]);
        else if (!ft_strncmp(data->file[i], "F ", 2))
            get_color(data->floor, ft_substr(data->file[i], 2, ft_strlen(data->file[i]) - 3));
        else if (!ft_strncmp(data->file[i], "C ", 2))
            get_color(data->ceiling, ft_substr(data->file[i], 2, ft_strlen(data->file[i]) - 3));
        else if (ft_strlen(data->file[i]) > 1)
            data->map = ft_splitjoin(data->map, data->file[i]);
    }
    if (!data->north || !data->south || !data->west || !data->east)
        return (true);
    return (false);
}
