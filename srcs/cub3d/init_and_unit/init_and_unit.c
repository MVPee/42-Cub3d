/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_unit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:07:42 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/16 17:27:46 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	free_data(t_data *data)
{
	// ft_free_matrix(2, &data->map, &data->file);
}

static bool	init_minimap(t_data *data)
{
	data->minimap->white = get_rgba(255, 255, 255, 255);
	data->minimap->transparent_white = get_rgba(255, 255, 255, 50);
	data->minimap->transparent_white = get_correct_color((u_int8_t *)&(data->minimap->transparent_white));
	data->minimap->transparent = get_rgba(0, 0, 0, 0);
	data->minimap->transparent = get_correct_color((u_int8_t *)&(data->minimap->transparent));
	data->minimap->black = get_rgba(0, 0, 0, 255);
	data->minimap->black = get_correct_color((u_int8_t *)&(data->minimap->black));
	data->minimap->transparent_black = get_rgba(0, 0, 0, 100);
	data->minimap->transparent_black = get_correct_color((u_int8_t *)&(data->minimap->transparent_black));
	data->minimap->image = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	data->minimap->map_input = (int **)malloc(sizeof(int *) * MINIMAP_SIZE);
	if (!data->minimap->map_input)
		return (true);
	for (int i = 0; i < MINIMAP_SIZE; i++)
	{
		data->minimap->map_input[i] = (int *)malloc(sizeof(int) * MINIMAP_SIZE);
		if (!data->minimap->map_input[i])
			return (true);
	}
	data->minimap->map_output = (int **)malloc(sizeof(int *) * (MINIMAP_SIZE
				+ 1));
	if (!data->minimap->map_output)
		return (true);
	for (int i = 0; i < MINIMAP_SIZE; i++)
	{
		data->minimap->map_output[i] = (int *)malloc(sizeof(int)
				* MINIMAP_SIZE);
		if (!data->minimap->map_output[i])
			return (true);
	}
	return (false);
}

bool	init_data(t_data *data)
{
	mlx_texture_t	*texture;

	data->north_image = NULL;
	data->south_image = NULL;
	data->west_image = NULL;
	data->east_image = NULL;
	data->file = NULL;
	data->map = NULL;
	data->mlx = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, false);
	if (!data->mlx)
		return (true);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->player = (t_player_pos *)malloc(sizeof(t_player_pos));
	if (!data->player)
		return (true);
	data->minimap = (t_minimap *)malloc(sizeof(t_minimap));
	if (!data->minimap)
		return (true);
	data->keys = (bool *)malloc(sizeof(bool) * 512);
	for (int i = 0; i < 512; i++)
        data->keys[i] = false;
	data->player->x = 0;
	data->player->y = 0;
	data->player->angle = 0;
	data->wall_dir = -1;
	if (init_minimap(data))
		return (true);
	return (false);
}
