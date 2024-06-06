/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:37:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/06 10:45:59 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void get_all_possible_paths(char **map)
{
    int y;
    int x;
    bool flag;

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
                if (map[y][x] == 'N')
                {
                    if (map[y - 1][x] == '0')
                    {
                        map[y - 1][x] = 'N';
                        flag = true;
                    }
                    if (map[y + 1][x] == '0')
                    {
                        map[y + 1][x] = 'N';
                        flag = true;
                    }
                    if (map[y][x - 1] == '0')
                    {
                        map[y][x - 1] = 'N';
                        flag = true;
                    }
                    if (map[y][x + 1] == '0')
                    {
                        map[y][x + 1] = 'N';
                        flag = true;
                    }
                }
            }
        }
    }
}

static void map_optimization(char **map, int *n)
{
    int y;
    int x;
    
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
            if (map[y][x] == 'N')
                map[y][x] = '0';
        }
    }
    map[n[0]][n[1]] = 'N';
}

static void put_border(char **map)
{
    int y;
    int x;

    y = -1;
    while (map[++y])
    {
        x = -1;
        while (map[y][++x])
        {
            if (map[y][x] == '0')
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

static void get_new_map(char **map)
{
    int n[2];
    int y;
    int x;

    y = -1;
    while (map[++y])
    {
        x = -1;
        while (map[y][++x])
        {
            if (map[y][x] == 'N')
            {
                n[0] = y;
                n[1] = x;
            }
        }
    }
    get_all_possible_paths(map);
    map_optimization(map, n);
    put_border(map);

    // Display
    int i = -1;
    while (++i < ft_splitlen((const char **)map))
        ft_printf("%d.\t%s\n", i, map[i]);
}

bool check_map(char **map)
{
    int y;
    int x;
    int count = 0;

    if (!map)
        return (true);
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
            if (map[y][x] == 'N')
                count++;
        }
    }
    if (count == 0)
        return (ft_printf_fd(2, "Error\nNo player online\n"), true);
    else if (count > 1)
        return (ft_printf_fd(2, "Error\nIt's not a multiplayer game\n"), true);
    get_new_map(map);
    return (false);
}
