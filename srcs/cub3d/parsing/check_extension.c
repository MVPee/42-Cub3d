/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:26:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/06 14:56:27 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

bool	check_extension(char *str)
{
	char	*temp;

	temp = ft_substr(str, ft_strlen(str) - 4, ft_strlen(str));
	if (!temp)
		return (perror("Malloc"), true);
	if (ft_strlen(str) < 5 || ft_strcmp(temp, ".cub"))
		return (ft_free(1, &temp), ft_printf_fd(2, \
				"Error\nInvalid map extension\n"), true);
	ft_free(1, &temp);
	return (false);
}
