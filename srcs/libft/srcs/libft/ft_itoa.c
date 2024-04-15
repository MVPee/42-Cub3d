/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:42:44 by mvpee             #+#    #+#             */
/*   Updated: 2023/11/15 08:56:37 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_int_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	ft_int_to_char(unsigned int number, char *nbr, int i)
{
	while (number > 0)
	{
		nbr[i] = '0' + (number % 10);
		number /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	int				i;
	char			*nbr;
	unsigned int	number;

	i = ft_int_len(n);
	nbr = (char *)malloc(sizeof(char) * (i + 1));
	if (!nbr)
		return (NULL);
	nbr[i--] = '\0';
	if (n == 0)
	{
		nbr[0] = '0';
	}
	if (n < 0)
	{
		nbr[0] = '-';
		n *= -1;
	}
	number = n;
	ft_int_to_char(number, nbr, i);
	return (nbr);
}
