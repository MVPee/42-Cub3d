/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_unit2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:41:53 by mvpee             #+#    #+#             */
/*   Updated: 2024/07/05 13:06:33 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_data(t_data *data)
{
	pid_t	pid;

	ft_free(2, &data->player, &data->keys);
	ft_free_matrix(1, &data->minimap->map_input);
	ft_free_matrix(1, &data->minimap->map_output);
	ft_free_matrix(2, &data->file, &data->map);
	ft_free(2, &data->minimap, &data->weapon);
	mlx_terminate(data->mlx);
	pid = fork();
	if (pid == 0)
		execlp("pkill", "pkill", "afplay", NULL);
	exit(0);
}

char	*get_weapon_path(int i)
{
	char	*str;
	char	*nbr;

	nbr = ft_itoa(i + 1);
	if (!nbr)
		return (NULL);
	str = ft_strjoin("rsrcs/sprites/weapons/weapon", nbr);
	if (!str)
		return (ft_free(1, &nbr), NULL);
	ft_free(1, &nbr);
	str = ft_strjoin_free(&str, ".png");
	if (!str)
		return (NULL);
	return (str);
}
