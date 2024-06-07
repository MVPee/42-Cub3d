/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:08:42 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/07 12:39:04 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	find_error(t_data *data)
{
	if (!data->north_image)
		ft_printf_fd(2, "Error\nCan you put a valid north_path texture please?!\n");
	if (!data->south_image)
		ft_printf_fd(2, "Error\nCan you put a valid south_path texture please?!\n");
	if (!data->west_image)
		ft_printf_fd(2, "Error\nCan you put a valid west_path texture please?!\n");
	if (!data->east_image)
		ft_printf_fd(2, "Error\nCan you put a valid east_path texture please?!\n");
}

static void	get_texture(t_data *data, img_t **image, char *line)
{
	char *str;
	mlx_texture_t *texture;
	
	str = ft_substr(line, 3, ft_strlen(line) - 4);
	texture = mlx_load_png(str);
	if (!texture)
		return ;
	*image = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	ft_free(2, &str, &line);
}

static void	get_color(int *color, char *line)
{
	char	**split;
	int		i;
	int 	array[3];

	ft_memset(array, 0, 3);
	i = -1;
	split = ft_split(line, ", ");
	if (split)
	{
		while (++i < 3 && split[i])
		{
			array[i] = ft_atoi(split[i]);
			if (array[i] < 0)
				array[i] = 0;
			if (array[i] > 255)
				array[i] = 255;
		}
		ft_free_matrix(1, &split);
	}
	ft_free(1, &line);
	*color = get_rgba(array[0], array[1], array[2], 255);
}

bool	check_file(t_data *data)
{
	int	i;
	i = -1;
	while (data->file[++i])
	{
		if (!ft_strncmp(data->file[i], "NO ", 3))
			get_texture(data, &data->north_image, data->file[i]);
		else if (!ft_strncmp(data->file[i], "SO ", 3))
			get_texture(data, &data->south_image, data->file[i]);
		else if (!ft_strncmp(data->file[i], "WE ", 3))
			get_texture(data, &data->west_image, data->file[i]);
		else if (!ft_strncmp(data->file[i], "EA ", 3))
			get_texture(data, &data->east_image, data->file[i]);
		else if (!ft_strncmp(data->file[i], "F ", 2))
			get_color(&data->floor_color, ft_substr(data->file[i], 2, \
					ft_strlen(data->file[i]) - 3));
		else if (!ft_strncmp(data->file[i], "C ", 2))
			get_color(&data->ceiling_color, ft_substr(data->file[i], 2, \
					ft_strlen(data->file[i]) - 3));
		else if (ft_strlen(data->file[i]) > 1)
			data->map = ft_splitjoin(data->map, data->file[i]);
	}
	if (!data->north_image || !data->south_image || !data->west_image || !data->east_image)
		return (find_error(data), true);
	return (false);
}
