/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:21:03 by mvan-pee          #+#    #+#             */
/*   Updated: 2023/11/15 08:57:11 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memset(void *ptr, int value, size_t count)
{
	unsigned char	*p;
	size_t			i;

	p = ptr;
	i = -1;
	while (++i < count)
		p[i] = value;
	return (p);
}
