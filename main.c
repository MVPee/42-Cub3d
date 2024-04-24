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

static bool check_map(char **map)
{
    int y;
    int x;

    y = -1;
    while(map[++y])
    {
        x = -1;
        while(map[y][++x])
        {
            if ((map[y][x] != '1' && map[y][x] != '0' && map[y][x] != ' ' && map[y][x] != 'N') && !ft_isspace(map[y][x]))
                return (ft_printf_fd(2, "Error\nInvalid map in y:%d x:%d c:'%c'\n", y, x, map[y][x]), true);
            if (y == 0 && (map[y][x] == '0' || map[y][x] == 'N'))
                return (ft_printf_fd(2, "Error\nBad Border\n"), true);
            else if (y == ft_splitlen((const char **)map) - 1 && (map[y][x] == '0' || map[y][x] == 'N'))
                return (ft_printf_fd(2, "Error\nBad Border\n"), true);
            else if (map[y][x] == '0' || map[y][x] == 'N')
            {
                if (x == 0)
                    return (ft_printf_fd(2, "Error\nBad Border\n"), true);
                if (ft_isspace(map[y - 1][x]) || ft_isspace(map[y][x - 1]) || ft_isspace(map[y + 1][x]) || ft_isspace(map[y][x + 1]))
                    return (ft_printf_fd(2, "Error\nBad Border\n"), true);
            }
        }
    }
    return (false);
}

static bool check_extension(char *str)
{
    char *temp;

    temp = ft_substr(str, ft_strlen(str) - 4, ft_strlen(str));
    if (!temp)
        return (perror("Malloc failed\n"), true);
    if (ft_strlen(str) < 5 || ft_strcmp(temp, ".cub"))
        return (ft_free(1, &temp), ft_printf_fd(2, "Error\nInvalid map extension\n"), true);
    ft_free(1, &temp);
    return (false);
}

int main(int ac, char **av)
{
    char *temp;
    char **map;

    if (ac != 2)
        return (ft_printf_fd(2, "Error\nNumber of argument(s)\n"), 1);

    // Extension Check
    if (check_extension(av[1]))
        return (1);

    // Get map
    if (temp = ft_read(open(av[1], O_RDONLY)))
        map = ft_split(temp, "\n");
    else
        return (1);
    ft_free(1, &temp);

    // Check map
    if (check_map(map))
        return (1);
    
    return (0);
}
