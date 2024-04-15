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

    if (ac != 2)
        return (ft_printf_fd(2, "Error\nNumber of argument(s)\n"), 1);
    temp = ft_substr(av[1], ft_strlen(av[1]) - 4, ft_strlen(av[1]));
    if (!temp)
        return (perror("Malloc failed\n"), 1);
    if (ft_strlen(av[1]) < 5 || ft_strcmp(temp, ".cub"))
        return (ft_free(1, &temp), ft_printf_fd(2, "Error\nInvalid map\n"), 1);
    return (ft_free(1, &temp), 0);
}
