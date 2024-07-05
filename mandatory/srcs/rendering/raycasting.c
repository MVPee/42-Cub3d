/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:22:06 by nechaara          #+#    #+#             */
/*   Updated: 2024/07/05 12:58:35 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	pixel_puter(t_raycast *vars, t_data *data)
{
	if (vars->distance != -1)
	{
		vars->y = -1;
		while (++vars->y < (int)vars->wall_height)
		{
			vars->texture_y = (vars->y * vars->wall_img->height)
				/ (int)vars->wall_height;
			if ((uint32_t)(vars->y + (HEIGHT - (int)vars->wall_height)
				/ 2) < data->image->height)
			{
				vars->color = get_correct_color(&((u_int8_t *) \
					vars->wall_img->pixels)[(vars->texture_y * \
					vars->wall_img->width + vars->texture_x) * 4]);
				mlx_put_pixel(data->image, vars->x, (float)vars->y
					+ ((float)HEIGHT - vars->wall_height) / 2, vars->color);
			}
		}
	}
}

static void	wall_height_and_orientation(t_data *data, t_raycast *vars)
{
	if (vars->wall_height - (int)vars->wall_height > 0.5)
		vars->wall_height += 1;
	if (data->wall_dir == 'E' || data->wall_dir == 'W')
		vars->hit_pos = vars->hit_y / PIXEL;
	else
		vars->hit_pos = vars->hit_x / PIXEL;
	if (data->wall_dir == 'N')
		vars->wall_img = data->south_image;
	else if (data->wall_dir == 'S')
		vars->wall_img = data->north_image;
	else if (data->wall_dir == 'E')
		vars->wall_img = data->west_image;
	else if (data->wall_dir == 'W')
		vars->wall_img = data->east_image;
}

static void	raycaster_loop(t_raycast vars, t_data *data)
{
	float	v_dist;
	float	p_angle;
	float	ray_angle;
	float	corr_dist;

	vars.x = -1;
	p_angle = data->player->angle;
	while (++vars.x < WIDTH)
	{
		v_dist = (WIDTH / (2 * tan(((float)FOV / 2.0f) * RADIANT)));
		ray_angle = p_angle + atan((vars.x - WIDTH / 2.0f) / v_dist) * F_PI;
		vars.distance = get_distance(data, ray_angle, &vars.hit_x, &vars.hit_y);
		corr_dist = vars.distance * cos((ray_angle - p_angle) * RADIANT);
		vars.wall_height = (PIXEL * v_dist) / corr_dist;
		wall_height_and_orientation(data, &vars);
		vars.texture_x = (int)(vars.hit_pos * vars.wall_img->width)
			% vars.wall_img->width;
		pixel_puter(&vars, data);
	}
}

void	raycasting(t_data *data)
{
	t_raycast	vars;
	int			i;
	int			j;
	int			transparent;

	vars.x = -1;
	transparent = get_rgba(0, 0, 0, 0);
	transparent = get_correct_color((u_int8_t *)&(transparent));
	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
			mlx_put_pixel(data->image, i, j, transparent);
	}
	raycaster_loop(vars, data);
}
