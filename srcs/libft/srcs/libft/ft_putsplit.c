/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:35:23 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/07 10:54:05 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putsplit(char **split, char *message_before)
{
	int	i;

	if (!split || !message_before)
		return ;
	i = -1;
	while (split[++i])
		ft_printf("%d. %s _%s_\n", i, message_before, split[i]);
}
