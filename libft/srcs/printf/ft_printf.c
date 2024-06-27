/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:12:15 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/03/11 21:14:07 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_is_for_printf(char a)
{
	if (a == 'c' || a == 's' || a == 'p' || a == 'd' || a == 'i' || a == 'u'
		|| a == 'x' || a == 'X' || a == '%')
		return (1);
	return (0);
}

static int	ft_checkflag(va_list args, char a, int *len, int fd)
{
	int	temp;

	temp = 0;
	if (a == 'c')
		temp = ft_putchar_fd_l(va_arg(args, int), fd);
	else if (a == 's')
		temp = ft_putstr_fd_l(va_arg(args, char *), fd);
	else if (a == 'p')
		temp = ft_pointer(va_arg(args, size_t), fd);
	else if (a == 'd' || a == 'i')
		temp = ft_putnbr_fd_l(va_arg(args, int), fd);
	else if (a == 'u')
		temp = ft_u_putnbr_fd_l(va_arg(args, unsigned int), fd);
	else if (a == 'x' || a == 'X')
		temp = ft_hexadecimal(va_arg(args, unsigned int), a, fd);
	else if (a == '%')
		temp = ft_putchar_fd_l('%', 1);
	else
		return (-1);
	if (temp < 0)
		*len = -1;
	else
		*len += temp;
	return (*len);
}

static int	executor_format(const char *format, va_list args, int *len_ptr,
		int fd)
{
	int	i;
	int	len;

	i = 0;
	len = *len_ptr;
	while (format[i])
	{
		if (format[i] == '%' && ft_is_for_printf(format[i + 1]))
		{
			len = ft_checkflag(args, format[i + 1], &len, fd);
			if (len < 0)
				return (-1);
			i++;
		}
		else
		{
			len += ft_putchar_fd_l(format[i], fd);
			if (len < 0)
				return (-1);
		}
		i++;
	}
	*len_ptr = len;
	return (0);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, format);
	if (executor_format(format, args, &len, fd) < 0)
	{
		va_end(args);
		return (-1);
	}
	va_end(args);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, format);
	if (executor_format(format, args, &len, 1) < 0)
	{
		va_end(args);
		return (-1);
	}
	va_end(args);
	return (len);
}
