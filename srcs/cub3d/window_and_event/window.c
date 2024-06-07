/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:46 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/07 11:57:04 by mvpee            ###   ########.fr       */
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
	mlx_image_to_window(data->mlx, data->ceiling_image, 0, 0);
    mlx_image_to_window(data->mlx, data->floor_image, 0, HEIGHT/2);
	return (false);	
}

static bool	window_init(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, true);
	if (!data->mlx)
		return (mlx_strerror(mlx_errno), true);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
		return (mlx_terminate(data->mlx), mlx_strerror(mlx_errno), true);
	if (get_background(data))
		return (mlx_terminate(data->mlx), mlx_strerror(mlx_errno), true);
	return (false);
}

int	game_loop(t_data *data)
{
	t_pos	player_pos;
	
	if (!data)
		return (EXIT_FAILURE);
	else if(window_init(data))
		return (error_handler(WIN_INIT_FAILED));
	mlx_key_hook(data->mlx, move_keyhook, &player_pos);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
