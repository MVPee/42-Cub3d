/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:46 by nechaara          #+#    #+#             */
/*   Updated: 2024/07/03 17:23:15 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	key_callback(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key < 512)
	{
		if (keydata.action == MLX_PRESS)
			data->keys[keydata.key] = true;
		else if (keydata.action == MLX_RELEASE)
			data->keys[keydata.key] = false;
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		free_data(data);
		exit(EXIT_SUCCESS);
	}
}

static void	window_init(t_data *data)
{
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap->image, WIDTH - MINIMAP_SIZE
		- 25, 25);
	mlx_image_to_window(data->mlx, data->weapon_img, WIDTH - (WEAPON_SIZE * 2),
		HEIGHT - WEAPON_SIZE);
}

int	game_loop(t_data *data)
{
	if (!data)
		return (EXIT_FAILURE);
	window_init(data);
	mlx_key_hook(data->mlx, key_callback, data);
	mlx_loop_hook(data->mlx, move_keyhook, data);
	mlx_loop(data->mlx);
	return (EXIT_SUCCESS);
}
