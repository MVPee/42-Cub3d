/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:43:50 by mvpee             #+#    #+#             */
/*   Updated: 2023/11/19 16:43:50 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_read(int fd)
{
	char	*line;
	char	*file;
	char	*temp;

	if (fd <= 0)
	{
		ft_printf_fd(2, RED "Error\nCannot read file.\n" RESET);
		return (NULL);
	}
	file = ft_strdup("");
	line = get_next_line(fd);
	if (!line)
	{
		free(file);
		ft_printf_fd(2, RED "Error\nEmpty map.\n" RESET);
		return (NULL);
	}
	while (line)
	{
		temp = file;
		file = ft_strjoin_ff(&temp, line);
		line = get_next_line(fd);
	}
	close(fd);
	return (file);
}
