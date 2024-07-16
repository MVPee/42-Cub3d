/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_unit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:07:42 by nechaara          #+#    #+#             */
/*   Updated: 2024/07/16 17:54:56 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_data(t_data *data)
{
	ft_free(1, &data->keys, &data->keys);
	ft_free(1, &data->player, &data->keys);
	ft_free_matrix(2, &data->file, &data->map);
	if (data->mlx)
		mlx_terminate(data->mlx);
}

bool	init_data(t_data *data)
{
	ft_null(9, &data->north_image, &data->south_image, &data->keys, &data->mlx, \
		&data->west_image, &data->east_image, &data->file, &data->map, &data->player);
	data->mlx = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, false);
	if (!data->mlx)
		return (true);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->floor_image = mlx_new_image(data->mlx, WIDTH, HEIGHT / 2);
	data->ceiling_image = mlx_new_image(data->mlx, WIDTH, HEIGHT / 2);
	if (!data->image || !data->floor_image || !data->ceiling_image)
		return (true);
	data->player = (t_player_pos *)malloc(sizeof(t_player_pos));
	if (!data->player)
		return (true);
	data->keys = (bool *)malloc(sizeof(bool) * 512);
	if (!data->keys)
		return (true);
	ft_memset(data->keys, false, 512);
	data->ceiling_color = -1;
	data->floor_color = -1;
	return (false);
}
