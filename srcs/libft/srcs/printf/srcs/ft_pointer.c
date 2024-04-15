/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:14:13 by mvpee             #+#    #+#             */
/*   Updated: 2023/11/15 10:35:45 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static int	print_pointer_address(size_t x, char *base, int fd)
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
		x = x / 16;
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

int	ft_pointer(size_t x, int fd)
{
	char	base[17];
	int		len;
	int		result;

	ft_strlcpy(base, "0123456789abcdef", sizeof(base));
	if (write(fd, "0x", 2) < 0)
		return (-1);
	len = 2;
	if (x == 0)
	{
		if (write(fd, "0", 1) < 0)
			return (-1);
		len++;
	}
	else
	{
		result = print_pointer_address(x, base, fd);
		if (result < 0)
			return (-1);
		len += result;
	}
	return (len);
}
