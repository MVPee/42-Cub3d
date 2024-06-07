/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:26:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/07 13:20:10 by mvpee            ###   ########.fr       */
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
		return (ft_free(1, &temp), ft_printf_fd(2, RED\
				"Error\nInvalid map extension\n" RESET), true);
	ft_free(1, &temp);
	return (false);
}
