/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:46 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/07 10:29:16 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool	window_init(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, true);
	if (!data->mlx)
	{
		mlx_strerror(mlx_errno);
		return (false);
	}
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
	{
		mlx_terminate(data->mlx);
		mlx_strerror(mlx_errno);
		return (false);
	}

	data->floor_image = mlx_new_image(data->mlx, WIDTH, HEIGHT/2);
	if (!data->floor_image)
	{
		mlx_terminate(data->mlx);
		mlx_strerror(mlx_errno);
		return (false);
	}
	for (int y = 0; y < data->floor_image->height; ++y)
        for (int x = 0; x < data->floor_image->width; ++x)
            ((int32_t*)data->floor_image->pixels)[y * data->floor_image->width + x] = data->floor_color;

	data->ceiling_image = mlx_new_image(data->mlx, WIDTH, HEIGHT/2);
	if (!data->ceiling_image)
	{
		mlx_terminate(data->mlx);
		mlx_strerror(mlx_errno);
		return (false);
	}
	for (int y = 0; y < data->ceiling_image->height; ++y)
        for (int x = 0; x < data->ceiling_image->width; ++x)
            ((int32_t*)data->ceiling_image->pixels)[y * data->ceiling_image->width + x] = data->ceiling_color;

	mlx_image_to_window(data->mlx, data->floor_image, 0, 0);
    mlx_image_to_window(data->mlx, data->ceiling_image, 0, HEIGHT/2);

	return (true);
}

int	game_loop(t_data *data)
{
	t_pos	player_pos;
	
	if (!data)
		return (EXIT_FAILURE);
	else if(!window_init(data))
		return (error_handler(WIN_INIT_FAILED));
	mlx_key_hook(data->mlx, move_keyhook, &player_pos);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
