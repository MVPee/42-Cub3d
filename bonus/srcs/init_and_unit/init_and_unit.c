/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_unit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:07:42 by nechaara          #+#    #+#             */
/*   Updated: 2024/07/17 09:59:58 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_minimap_color(t_minimap *minimap)
{
	minimap->white = get_rgba(255, 255, 255, 255);
	minimap->door = get_rgba_transparency(255, 255, 255, 75);
	minimap->door = \
		get_correct_color((u_int8_t *)&(minimap->door));
	minimap->transparent_white = get_rgba_transparency(255, 255, 255, 50);
	minimap->transparent_white = \
		get_correct_color((u_int8_t *)&(minimap->transparent_white));
	minimap->transparent = get_rgba_transparency(0, 0, 0, 0);
	minimap->transparent = \
		get_correct_color((u_int8_t *)&(minimap->transparent));
	minimap->black = get_rgba(0, 0, 0, 255);
	minimap->black = \
		get_correct_color((u_int8_t *)&(minimap->black));
	minimap->transparent_black = get_rgba_transparency(0, 0, 0, 100);
	minimap->transparent_black = \
		get_correct_color((u_int8_t *)&(minimap->transparent_black));
}

static bool	init_minimap2(t_data *data)
{
	int	i;

	data->minimap->map_output = (int **)malloc(sizeof(int *) * (MINIMAP_SIZE
				+ 1));
	if (!data->minimap->map_output)
		return (true);
	data->minimap->map_output[MINIMAP_SIZE] = NULL;
	i = -1;
	while (++i < MINIMAP_SIZE)
	{
		data->minimap->map_output[i] = (int *)malloc(sizeof(int)
				* MINIMAP_SIZE);
		if (!data->minimap->map_output[i])
			return (ft_free_matrix(1, &data->minimap->map_output), true);
	}
	return (false);
}

static bool	init_minimap(t_data *data)
{
	int	i;

	init_minimap_color(data->minimap);
	data->minimap->map_input = NULL;
	data->minimap->map_output = NULL;
	data->minimap->image = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!data->minimap->image)
		return (true);
	data->minimap->map_input = (int **)malloc(sizeof(int *) * (MINIMAP_SIZE
				+ 1));
	if (!data->minimap->map_input)
		return (true);
	data->minimap->map_input[MINIMAP_SIZE] = NULL;
	i = -1;
	while (++i < MINIMAP_SIZE)
	{
		data->minimap->map_input[i] = (int *)malloc(sizeof(int) * MINIMAP_SIZE);
		if (!data->minimap->map_input[i])
			return (ft_free_matrix(1, &data->minimap->map_input), true);
	}
	if (init_minimap2(data))
		return (ft_free_matrix(1, &data->minimap->map_input), true);
	data->ceiling_color = -1;
	data->floor_color = -1;
	return (false);
}

static bool	init_weapon(t_data *data)
{
	int				i;
	char			*str;
	mlx_texture_t	*texture;

	data->weapon = malloc(sizeof(t_img *) * 5);
	if (!data->weapon)
		return (true);
	i = -1;
	while (++i < 5)
	{
		str = get_weapon_path(i);
		if (!str)
			return (ft_free(1, &data->weapon), true);
		texture = mlx_load_png(str);
		ft_free(1, &str);
		if (!texture)
			return (ft_free(1, &data->weapon), true);
		data->weapon[i] = mlx_texture_to_image(data->mlx, texture);
		mlx_delete_texture(texture);
		if (!data->weapon[i])
			return (ft_free(1, &data->weapon), true);
	}
	return (false);
}

bool	init_data(t_data *data)
{
	ft_null(8, &data->north_image, &data->south_image, &data->keys, \
		&data->west_image, &data->east_image, &data->file, &data->map, \
		&data->player);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->weapon_img = mlx_new_image(data->mlx, WEAPON_SIZE, WEAPON_SIZE);
	if (!data->image || !data->weapon_img)
		return (true);
	data->player = (t_player_pos *)malloc(sizeof(t_player_pos));
	if (!data->player)
		return (true);
	data->minimap = (t_minimap *)malloc(sizeof(t_minimap));
	if (!data->minimap)
		return (ft_free(1, &data->player), true);
	data->keys = (bool *)malloc(sizeof(bool) * 512);
	if (!data->keys)
		return (ft_free(2, &data->player, &data->minimap), true);
	ft_memset(data->keys, false, 512);
	if (init_minimap(data))
		return (ft_free(3, &data->player, &data->minimap, &data->keys), true);
	if (init_weapon(data))
		return (ft_free(3, &data->player, &data->minimap, &data->keys), true);
	return (false);
}
