/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:28:06 by mvpee             #+#    #+#             */
/*   Updated: 2023/11/15 08:56:18 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_atoi(const char *nptr)
{
	unsigned long	nbr;
	int				sign;

	sign = 1;
	nbr = 0;
	while ((*nptr != '\0') && ((*nptr == 32) || (*nptr >= 9 && *nptr <= 13)))
		nptr++;
	if (*nptr == 45)
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == 43)
		nptr++;
	while ((*nptr != '\0') && (*nptr >= 48 && *nptr <= 57))
	{
		nbr = (nbr * 10) + (*nptr - 48);
		nptr++;
		if ((nbr > LONG_MAX) && (sign == 1))
			return (-1);
		else if ((nbr > LONG_MAX) && (sign == -1))
			return (0);
	}
	return (nbr * sign);
}
