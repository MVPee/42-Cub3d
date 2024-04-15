/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:15:12 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/07 10:50:10 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static int	is_valid_char(char c, int base)
{
	if ((base <= 10 && (c >= '0' && c < '0' + base))
		|| (base > 10 && ((c >= '0' && c <= '9')
				|| (c >= 'a' && c < 'a' + base - 10)
				|| (c >= 'A' && c < 'A' + base - 10))))
		return (1);
	return (0);
}

static int	get_digit_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (0);
}

static void	handle_sign_and_prefix(const char **s, int *sign, int *base)
{
	while (is_whitespace(**s))
		(*s)++;
	if (**s == '-')
	{
		*sign = -1;
		(*s)++;
	}
	else if (**s == '+')
	{
		*sign = 1;
		(*s)++;
	}
	if ((*base == 0 || *base == 16) && **s == '0')
	{
		*s += 1;
		if (**s == 'x' || **s == 'X')
		{
			*s += 1;
			*base = 16;
		}
		else
			*base = 8;
	}
	if (*base == 0)
		*base = 10;
}

/**
 * @brief
 * The ft_strtol function converts the initial portion of the string pointed
 * to by nptr to a long integer representation. It skips leading whitespaces,
 * handles an optional sign, and converts digits until a non-numeric character
 * is encountered. The function behaves similarly to the standard strtol
 * function but without the overflow/underflow check.
 *
 * @param nptr Pointer to the character string.
 * @param endptr If not NULL, stores the address of the next character after 
 * the numerical value.
 * @param base The base for the conversion (0 for auto-detection, 
 * or between 2 and 36).
 *
 * @return long The converted long integer.
 */
long	ft_strtol(const char *nptr, char **endptr, int base)
{
	const char	*s;
	long		result;
	int			sign;
	int			digit;

	s = nptr;
	result = 0;
	sign = 1;
	handle_sign_and_prefix(&s, &sign, &base);
	while (is_valid_char(*s, base))
	{
		digit = get_digit_value(*s++);
		result = result * base + digit;
	}
	if (endptr)
		*endptr = (char *)s;
	return (result * sign);
}
