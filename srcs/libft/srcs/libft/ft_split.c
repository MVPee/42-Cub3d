/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:35:25 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/07 15:09:07 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	total_strings(char const *s, char *str)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (ft_ischarin(s[i], str)))
			i++;
		if (s[i])
			count++;
		while (s[i] && !(ft_ischarin(s[i], str)))
			i++;
	}
	return (count);
}

static int	sep_len(char const *s, char *str)
{
	int	i;

	i = 0;
	while (s[i] && !(ft_ischarin(s[i], str)))
		i++;
	return (i);
}

static char	*ft_word(char const *s, char *str)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = sep_len(s, str);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	while (i < len_word)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*free_memory(char **strings, int i)
{
	while (i-- > 0)
		free(strings[i]);
	free(strings);
	return (NULL);
}

char	**ft_split(char const *s, char *str)
{
	char	**split;
	int		i;

	if (!s || !str)
		return (NULL);
	i = 0;
	split = (char **)malloc(sizeof(char *) * (total_strings(s, str) + 1));
	if (!split)
		return (NULL);
	while (*s)
	{
		if (!ft_ischarin(*s, str))
		{
			split[i] = ft_word(s, str);
			if (split[i++] == NULL)
				return (free_memory(split, i));
			s += sep_len(s, str);
		}
		if (*s)
			s++;
	}
	split[i] = NULL;
	return (split);
}
