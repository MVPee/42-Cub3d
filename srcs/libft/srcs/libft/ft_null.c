/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:33:04 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/16 11:34:02 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_null(unsigned int count, ...)
{
	va_list	args;
	void	**tmp;

	va_start(args, count);
	while (count--)
	{
		tmp = va_arg(args, void **);
		*tmp = NULL;
	}
	va_end(args);
}
