/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:49:34 by mvpee             #+#    #+#             */
/*   Updated: 2023/11/15 10:35:17 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static int	print_hexadecimal(unsigned int x, char *base, int fd)
{
	char	string[25];
	int		i;
	int		len;
	int		temp;

	i = 0;
	len = 0;
	while (x != 0)
	{
		string[i++] = base[x % 16];
		x /= 16;
	}
	while (i--)
	{
		temp = ft_putchar_fd_l(string[i], fd);
		if (temp < 0)
			return (-1);
		len += temp;
	}
	return (len);
}

int	ft_hexadecimal(unsigned int x, char a, int fd)
{
	char	base[17];
	int		len;
	int		result;

	if (a == 'X')
		ft_strlcpy(base, "0123456789ABCDEF", sizeof(base));
	else
		ft_strlcpy(base, "0123456789abcdef", sizeof(base));
	if (x == 0)
	{
		result = ft_putchar_fd_l('0', fd);
		if (result < 0)
			return (-1);
		return (result);
	}
	result = print_hexadecimal(x, base, fd);
	if (result < 0)
		return (-1);
	len = result;
	return (len);
}
