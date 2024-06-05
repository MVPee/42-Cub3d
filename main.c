/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:53:08 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/04/15 09:53:08 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void free_data(t_data *data)
{
    ft_free(4, &data->north, &data->south, &data->west, &data->east);
    ft_free(2, &data->floor, &data->ceiling);
    ft_free_matrix(2, &data->map, &data->file);
}

int init_data(t_data *data)
{
    int i;

    data->floor = (int *)malloc(sizeof(int) * 3);
    if (!data->floor)
        return (1);
    i = -1;
    while(++i < 3)
        data->floor[i] = 0;
    data->ceiling = (int *)malloc(sizeof(int) * 3);
    if (!data->ceiling)
        return (ft_free_matrix(1, &data->floor), 1);
    i = -1;
    while(++i < 3)
        data->ceiling[i] = 0;
    data->north = NULL;
    data->south = NULL;
    data->west = NULL;
    data->east = NULL;
    data->file = NULL;
    data->map = NULL;
    return (0);
}

int main(int ac, char **av)
{
    t_data data;
    char *temp;

    if (ac != 2)
        return (ft_printf_fd(2, "Error\nNumber of argument(s)\n"), 1);

    if (init_data(&data))
        return (ft_printf_fd(2, "Error\nMalloc failed\n"), 1);

    // Extension Check
    if (check_extension(av[1]))
        return (free_data(&data), 1);

    // Get map
    if ((temp = ft_read(open(av[1], O_RDONLY))))
        data.file = ft_split(temp, "\n");
    else
        return (free_data(&data), 1);
    ft_free(1, &temp);

    // Check file
    if (check_file(&data))
        return (free_data(&data), ft_printf_fd(2, "Error\nInvalid setting(s)\n"),1);

    // Check map
    if (check_map(data.map))
        return (free_data(&data), 1);
    
    return (free_data(&data), 0);
}
