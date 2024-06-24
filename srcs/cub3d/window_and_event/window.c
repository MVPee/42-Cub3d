/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:46 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/24 10:08:31 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

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

static void	get_background(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < (int)data->floor_image->height)
	{
		x = -1;
		while (++x < (int)data->floor_image->width)
			((int32_t *)data->floor_image->pixels)[y * data->floor_image->width
				+ x] = data->floor_color;
	}
	y = -1;
	while (++y < (int)data->ceiling_image->height)
	{
		x = -1;
		while (++x < (int)data->ceiling_image->width)
			((int32_t *)data->ceiling_image->pixels)[y
				* data->ceiling_image->width + x] = data->ceiling_color;
	}
}

static void	window_init(t_data *data)
{
	get_background(data);
	mlx_image_to_window(data->mlx, data->ceiling_image, 0, 0);
	mlx_image_to_window(data->mlx, data->floor_image, 0, HEIGHT / 2);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap->image, WIDTH - MINIMAP_SIZE
		- 25, 25);
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
