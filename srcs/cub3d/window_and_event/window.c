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
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, true);
	if (!mlx)
	{
		mlx_strerror(mlx_errno);
		return (false);
	}
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
	{
		mlx_terminate(mlx);
		mlx_strerror(mlx_errno);
		return (false);
	}
	data->mlx = mlx;
	data->image = image;
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
