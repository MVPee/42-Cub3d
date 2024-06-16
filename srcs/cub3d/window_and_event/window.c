/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:46 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/16 17:27:40 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool get_background(t_data *data)
{
	int y;
	int x;

	data->floor_image = mlx_new_image(data->mlx, WIDTH, HEIGHT/2);
	if (!data->floor_image)
		return (mlx_terminate(data->mlx), mlx_strerror(mlx_errno), true);
	y = -1;
	while (++y < data->floor_image->height)
	{
		x = -1;
		while (++x < data->floor_image->width)
            ((int32_t*)data->floor_image->pixels)[y * data->floor_image->width + x] = data->floor_color;
	}
	data->ceiling_image = mlx_new_image(data->mlx, WIDTH, HEIGHT/2);
	if (!data->ceiling_image)
		return (mlx_terminate(data->mlx), mlx_strerror(mlx_errno), true);
	y = -1;
	while (++y < data->ceiling_image->height)
	{
		x = -1;
		while (++x < data->ceiling_image->width)
            ((int32_t*)data->ceiling_image->pixels)[y * data->ceiling_image->width + x] = data->ceiling_color;
	}
	return (false);	
}

static bool	window_init(t_data *data)
{
	if (get_background(data))
		return (mlx_terminate(data->mlx), mlx_strerror(mlx_errno), true);
	mlx_image_to_window(data->mlx, data->ceiling_image, 0, 0);
    mlx_image_to_window(data->mlx, data->floor_image, 0, HEIGHT/2);
	return (false);
}

static void key_callback(mlx_key_data_t keydata, void *param)
{
    t_data *data = (t_data *)param;

    if (keydata.key < 512)
	{
        if (keydata.action == MLX_PRESS)
            data->keys[keydata.key] = true;
		else if (keydata.action == MLX_RELEASE)
            data->keys[keydata.key] = false;
    }
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        exit(0);
}

int	game_loop(t_data *data)
{	
	if (!data)
		return (EXIT_FAILURE);
	else if(window_init(data))
		return (error_handler(WIN_INIT_FAILED));
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap->image, WIDTH - MINIMAP_SIZE - 25, 25);
	mlx_key_hook(data->mlx, key_callback, data);
	mlx_loop_hook(data->mlx, move_keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	if (data->minimap->image)
		mlx_delete_image(data->mlx, data->minimap->image);
	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	return (EXIT_SUCCESS);
}
