/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:21:02 by mvpee             #+#    #+#             */
/*   Updated: 2024/07/03 17:24:21 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_rgba_transparency(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (a << 24 | b << 16 | g << 8 | r);
}

bool	check_extension(char *str)
{
	char	*temp;

	temp = ft_substr(str, ft_strlen(str) - 4, ft_strlen(str));
	if (!temp)
		return (perror("Malloc"), true);
	if (ft_strlen(str) < 5 || ft_strcmp(temp, ".cub"))
		return (ft_free(1, &temp), ft_printf_fd(2,
				RED "Error\nInvalid map extension\n" RESET), true);
	ft_free(1, &temp);
	return (false);
}
