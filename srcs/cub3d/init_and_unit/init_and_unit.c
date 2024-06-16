/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_unit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:07:42 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/16 18:22:57 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	free_data(t_data *data)
{
	int i;

	ft_free(2, &data->player, &data->keys);
	ft_free_matrix(1, &data->minimap->map_input);
	ft_free_matrix(1, &data->minimap->map_output);
	ft_free(1, &data->minimap);
	mlx_terminate(data->mlx);
}

static void init_minimap_color(t_minimap *minimap)
{
	minimap->white = get_rgba(255, 255, 255, 255);
	minimap->transparent_white = get_rgba(255, 255, 255, 50);
	minimap->transparent_white = get_correct_color((u_int8_t *)&(minimap->transparent_white));
	minimap->transparent = get_rgba(0, 0, 0, 0);
	minimap->transparent = get_correct_color((u_int8_t *)&(minimap->transparent));
	minimap->black = get_rgba(0, 0, 0, 255);
	minimap->black = get_correct_color((u_int8_t *)&(minimap->black));
	minimap->transparent_black = get_rgba(0, 0, 0, 100);
	minimap->transparent_black = get_correct_color((u_int8_t *)&(minimap->transparent_black));
}

static bool	init_minimap(t_data *data)
{
	int i;

	init_minimap_color(data->minimap);
	data->minimap->image = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	data->minimap->map_input = (int **)malloc(sizeof(int *) * (MINIMAP_SIZE + 1));
	if (!data->minimap->map_input)
		return (true);
	data->minimap->map_input[MINIMAP_SIZE] = NULL;
	i = -1;
	while (++i < MINIMAP_SIZE)
	{
		data->minimap->map_input[i] = (int *)malloc(sizeof(int) * MINIMAP_SIZE);
		if (!data->minimap->map_input[i])
			return (true);
	}
	data->minimap->map_output = (int **)malloc(sizeof(int *) * (MINIMAP_SIZE + 1));
	if (!data->minimap->map_output)
		return (true);
	data->minimap->map_output[MINIMAP_SIZE] = NULL;
	i = -1;
	while (++i < MINIMAP_SIZE)
	{
		data->minimap->map_output[i] = (int *)malloc(sizeof(int) * MINIMAP_SIZE);
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
	data->floor_image = mlx_new_image(data->mlx, WIDTH, HEIGHT/2);
	data->ceiling_image = mlx_new_image(data->mlx, WIDTH, HEIGHT/2);
	if (!data->image || !data->floor_image || !data->ceiling_image)
		return (true);
	data->player = (t_player_pos *)malloc(sizeof(t_player_pos));
	if (!data->player)
		return (true);
	data->minimap = (t_minimap *)malloc(sizeof(t_minimap));
	if (!data->minimap)
		return (true);
	data->keys = (bool *)malloc(sizeof(bool) * 512);
	if (!data->keys)
		return (true);
	ft_memset(data->keys, false, 512);
	if (init_minimap(data))
		return (true);
	return (false);
}
