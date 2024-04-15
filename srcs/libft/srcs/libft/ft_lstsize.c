/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:38:28 by mvpee             #+#    #+#             */
/*   Updated: 2023/11/15 08:56:59 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*temp;

	temp = lst;
	if (!temp)
		return (0);
	len = 0;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}
