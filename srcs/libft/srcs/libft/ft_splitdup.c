/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@19.be>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:48:45 by mvpee             #+#    #+#             */
/*   Updated: 2023/11/19 12:14:22 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	free_strings(char **dest, int index)
{
	while (index >= 0)
	{
		free(dest[index]);
		index--;
	}
	free(dest);
}

static char	**copy_string_array(const char **src, char **dest, int index)
{
	if (src[index] == NULL)
	{
		dest[index] = NULL;
		return (dest);
	}
	dest[index] = ft_strdup(src[index]);
	if (dest[index] == NULL)
	{
		free_strings(dest, index - 1);
		return (NULL);
	}
	return (copy_string_array(src, dest, index + 1));
}

char	**ft_splitdup(const char **src)
{
	int		count;
	char	**dest;

	if (!src)
		return (NULL);
	count = 0;
	while (src[count] != NULL)
		count++;
	dest = (char **)malloc((count + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	return (copy_string_array(src, dest, 0));
}
