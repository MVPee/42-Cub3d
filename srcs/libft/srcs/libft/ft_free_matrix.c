/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:23:11 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/14 17:15:20 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_free_matrix(unsigned int count, ...)
{
	va_list	args;
	void	***array;
	int		i;

	va_start(args, count);
	while (count--)
	{
		array = va_arg(args, void ***);
		if (*array)
		{
			i = 0;
			while ((*array)[i])
			{
				free((*array)[i]);
				(*array)[i] = NULL;
				i++;
			}
			free(*array);
			*array = NULL;
		}
	}
	va_end(args);
}
