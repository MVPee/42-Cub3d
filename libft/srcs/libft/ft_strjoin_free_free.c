/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:57:18 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/16 09:55:46 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin_ff(char **s1, char *s2)
{
	char	*str;

	if (!s2)
	{
		if (!(*s1))
			str = ft_strdup("");
		else
			str = ft_strdup(*s1);
		return (ft_free(1, s1), str);
	}
	if (!(*s1))
		*s1 = ft_strdup("");
	if (!(*s1))
		return (ft_free(1, &s2), NULL);
	str = ft_strjoin(*s1, s2);
	if (!str)
		return (ft_free(2, s1, &s2), NULL);
	return (ft_free(2, s1, &s2), str);
}
