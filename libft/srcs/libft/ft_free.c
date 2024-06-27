/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:32:53 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/07 14:51:07 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_free(unsigned int count, ...)
{
	va_list	args;
	void	**tmp;

	va_start(args, count);
	while (count--)
	{
		tmp = va_arg(args, void **);
		if (*tmp)
		{
			free(*tmp);
			*tmp = NULL;
		}
	}
	va_end(args);
}
