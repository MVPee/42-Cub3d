/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splittrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:24:30 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/12 18:25:34 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	**ft_splittrim(char **split, char *set)
{
	int		i;
	int		count;
	char	**new_split;

	if (!split || !set)
		return (NULL);
	count = 0;
	while (split[count])
		count++;
	new_split = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_split)
		return (ft_free_matrix(1, &split), NULL);
	i = -1;
	while (++i < count)
	{
		new_split[i] = ft_strtrim(split[i], set);
		if (!new_split[i])
			return (ft_free_matrix(2, &new_split, &split), NULL);
	}
	new_split[count] = NULL;
	return (ft_free_matrix(1, &split), new_split);
}
