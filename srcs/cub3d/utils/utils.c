/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:36:30 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/06 13:38:50 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

bool error_handler(char *str)
{
    if (!str)
        return (false);
    ft_printf_fd(STDERR_FILENO, "%s\n", str);
    return (false);
}