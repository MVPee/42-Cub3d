/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:08:42 by mvpee             #+#    #+#             */
/*   Updated: 2024/07/16 17:17:49 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	find_error(t_data *data)
{
	if (!data->north_image || !data->south_image || !data->west_image
		|| !data->east_image || data->ceiling_color == -1
		|| data->floor_color == -1 || !data->door_image)
	{
		if (!data->north_image)
			ft_printf_fd(2, RED "Error\nPut a valid north texture\n" RESET);
		if (!data->south_image)
			ft_printf_fd(2, RED "Error\nPut a valid south texture\n" RESET);
		if (!data->west_image)
			ft_printf_fd(2, RED "Error\nPut a valid west texture\n" RESET);
		if (!data->east_image)
			ft_printf_fd(2, RED "Error\nPut a valid east texture\n" RESET);
		if (data->ceiling_color == -1)
			ft_printf_fd(2, RED "Error\nPut a valid ceiling color\n" RESET);
		if (data->floor_color == -1)
			ft_printf_fd(2, RED "Error\nPut a valid floor color\n" RESET);
		if (!data->door_image)
			ft_printf_fd(2, RED "Error\nPut a valid door texture\n" RESET);
		return (true);
	}
	return (false);
}

static void	get_texture(t_data *data, t_img **image, char *line)
{
	char			*str;
	char			*temp;
	mlx_texture_t	*texture;

	str = NULL;
	temp = NULL;
	if (*image)
		mlx_delete_image(data->mlx, *image);
	temp = ft_substr(line, 3, ft_strlen(line) - 4);
	str = ft_strtrim(temp, " ");
	texture = mlx_load_png(str);
	if (!texture)
	{
		ft_free(2, &str, &temp);
		return ;
	}
	*image = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	ft_free(2, &str, &temp);
}

static bool	get_color(int *color, char *line)
{
	char	**split;
	int		i;
	int		array[3];

	ft_memset(array, -1, 3);
	i = -1;
	split = ft_split(line, ", ");
	if (!split)
		return (true);
	if (split)
	{
		while (++i < 3 && split[i] && ft_splitlen((const char **)split) == 3 \
		&& ft_strlen(split[i]) < 4)
		{
			array[i] = ft_atoi(split[i]);
			if (array[i] < 0 || array[i] > 255 || array[i] == -1)
				return (true);
		}
		if (i != 3)
			return (true);
		ft_free_matrix(1, &split);
	}
	*color = get_rgba_transparency(array[0], array[1], array[2], 255);
	*color = get_correct_color((u_int8_t *)color);
	return (ft_free(1, &line), false);
}

static bool	check_line(t_data *data, int i)
{
	if (!ft_strncmp(data->file[i], "NO ", 3))
		get_texture(data, &data->north_image, data->file[i]);
	else if (!ft_strncmp(data->file[i], "SO ", 3))
		get_texture(data, &data->south_image, data->file[i]);
	else if (!ft_strncmp(data->file[i], "WE ", 3))
		get_texture(data, &data->west_image, data->file[i]);
	else if (!ft_strncmp(data->file[i], "EA ", 3))
		get_texture(data, &data->east_image, data->file[i]);
	else if (!ft_strncmp(data->file[i], "DO ", 3))
		get_texture(data, &data->door_image, data->file[i]);
	else if (!ft_strncmp(data->file[i], "F ", 2))
	{
		if (get_color(&data->floor_color, ft_substr(data->file[i], 2,
					ft_strlen(data->file[i]) - 3)))
			return (ft_printf_fd(2, RED FLOOR_COLOR RESET), true);
	}
	else if (!ft_strncmp(data->file[i], "C ", 2))
	{
		if (get_color(&data->ceiling_color, ft_substr(data->file[i], 2,
					ft_strlen(data->file[i]) - 3)))
			return (ft_printf_fd(2, RED CEILING_COLOR RESET), true);
	}
	else if (ft_strlen(data->file[i]) > 1)
		data->map = ft_splitjoin(data->map, data->file[i]);
	return (false);
}

bool	check_file(t_data *data)
{
	int	i;

	i = -1;
	while (data->file[++i])
		check_line(data, i);
	return (find_error(data));
}
