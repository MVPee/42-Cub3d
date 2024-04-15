/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:06:20 by mvpee             #+#    #+#             */
/*   Updated: 2023/10/13 18:06:20 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	ft_putstr_fd_l(char *s, int fd)
{
	int	i;
	int	len;
	int	temp;

	temp = 0;
	len = 0;
	if (!s)
		return (ft_putstr_fd_l("(null)", fd));
	i = -1;
	while (s[++i])
	{
		temp = ft_putchar_fd_l(s[i], fd);
		if (temp < 0)
			return (-1);
		len += temp;
	}
	return (len);
}
