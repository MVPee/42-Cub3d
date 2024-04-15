/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinchar_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:22:48 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/08 16:02:11 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoinchar_free(char **s1, char s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s2)
		return (NULL);
	if (!(*s1))
		*s1 = ft_strdup("");
	if (!(*s1))
		return (ft_free(1, s1), NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(*s1) + 2));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while ((*s1)[++i])
		str[j++] = (*s1)[i];
	str[j++] = s2;
	str[j] = '\0';
	ft_free(1, s1);
	return (str);
}
