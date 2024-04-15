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

int main(int ac, char **av)
{
    char *temp;
    char **map;
    int y;
    int x;

    if (ac != 2)
        return (ft_printf_fd(2, "Error\nNumber of argument(s)\n"), 1);
    temp = ft_substr(av[1], ft_strlen(av[1]) - 4, ft_strlen(av[1]));
    if (!temp)
        return (perror("Malloc failed\n"), 1);
    if (ft_strlen(av[1]) < 5 || ft_strcmp(temp, ".cub"))
        return (ft_free(1, &temp), ft_printf_fd(2, "Error\nInvalid map\n"), 1);
    ft_free(1, &temp);
    temp = ft_read(open(av[1], O_RDONLY));
    if (!temp)
        return (1);
    map = ft_split(temp, "\n");
    y = -1;
    while(map[++y])
        ft_printf("%d\t%s\n", y, map[y]);

    y = -1;
    while(map[++y])
    {
        x = -1;
        while(map[y][++x])
        {
            if ((map[y][x] != '1' && map[y][x] != '0' && map[y][x] != ' ' && map[y][x] != 'N') && !ft_isspace(map[y][x]))
                return (ft_printf_fd(2, "Error\nInvalid map in y:%d x:%d c:'%c'\n", y, x, map[y][x]), 1);
            if (y == 0 && (map[y][x] == '0' || map[y][x] == 'N'))
                return (ft_printf_fd(2, "Error\nBad Border\n"), 1);
            else if (y == ft_splitlen((const char **)map) - 1 && (map[y][x] == '0' || map[y][x] == 'N'))
                return (ft_printf_fd(2, "Error\nBad Border\n"), 1);
            else if (map[y][x] == '0' || map[y][x] == 'N')
            {
                if (x == 0)
                    return (ft_printf_fd(2, "Error\nBad Border\n"), 1);
                if (ft_isspace(map[y - 1][x]) || ft_isspace(map[y][x - 1]) || ft_isspace(map[y + 1][x]) || ft_isspace(map[y][x + 1]))
                    return (ft_printf_fd(2, "Error\nBad Border\n"), 1);
            }
        }
    }

    return (0);
}
