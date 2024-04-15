/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_string_number.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:34:11 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/07 10:54:24 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * @brief 
 * This functions checks if the string is a representation of a number.
 * @param str The string representing a number.
 * @return 1 or 0 depending on the result.
 */
int	ft_is_string_number(char *str)
{
	int	i;
	int	sign_count;

	i = 0;
	sign_count = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			sign_count++;
			if (i > 0)
				return (0);
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (ft_strlen(str) == 1 && sign_count == 1)
		return (0);
	return (1);
}
