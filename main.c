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
