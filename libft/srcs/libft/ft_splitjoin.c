/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:02:28 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/08 16:25:23 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	**ft_splitjoin(char **split, char *need_to_add_to_split)
{
	char	**new_split;
	int		count;
	int		i;

	count = 0;
	if (split)
		while (split[count])
			count++;
	new_split = (char **)malloc(sizeof(char *) * (count + 2));
	if (new_split == NULL)
		return (ft_free_matrix(1, &split), NULL);
	i = -1;
	while (++i < count)
		new_split[i] = ft_strdup(split[i]);
	new_split[count] = ft_strdup(need_to_add_to_split);
	if (!new_split[count])
		return (ft_free_matrix(2, &new_split, &split), NULL);
	new_split[count + 1] = NULL;
	ft_free_matrix(1, &split);
	return (new_split);
}
