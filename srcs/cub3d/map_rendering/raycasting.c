/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:22:06 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/10 23:58:13 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	pixel_puter(t_raycast *vars, t_data *data)
{
	if (vars->distance != -1)
	{
		vars->y = -1;
		while (++vars->y < (int)vars->wall_height)
		{
			vars->texture_y = (vars->y * vars->wall_img->height) \
				/ (int)vars->wall_height;
			if (vars->y + (HEIGHT - (int)vars->wall_height) \
				/ 2 < data->image->height)
			{
				vars->color = get_correct_color(&((u_int8_t *) \
					vars->wall_img->pixels)[(vars->texture_y * \
					vars->wall_img->width + vars->texture_x) * 4]);
				mlx_put_pixel(data->image, vars->x, (float)vars->y \
					+((float)HEIGHT - vars->wall_height) / 2, vars->color);
			}
		}
	}
}

static void	wall_height_and_orientation(t_data *data, t_raycast *vars)
{
	if (vars->wall_height - (int)vars->wall_height > 0.5)
		vars->wall_height += 1;
	if (data->wall_dir == 'E' || data->wall_dir == 'W')
		vars->hitPos = vars->hitY / PIXEL;
	else
		vars->hitPos = vars->hitX / PIXEL;
	if (data->wall_dir == 'N')
		vars->wall_img = data->north_image;
	else if (data->wall_dir == 'S')
		vars->wall_img = data->south_image;
	else if (data->wall_dir == 'E')
		vars->wall_img = data->east_image;
	else if (data->wall_dir == 'W')
		vars->wall_img = data->west_image;
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
		v_dist = (WIDTH / (2 * tan(((float) FOV / 2.0f) * RADIANT)));
		ray_angle = p_angle + atan((vars.x - WIDTH / 2.0f) / v_dist) * F_PI;
		vars.distance = get_distance(data, ray_angle, &vars.hitX, &vars.hitY);
		corr_dist = vars.distance * cos((ray_angle - p_angle) * RADIANT);
		vars.wall_height = (PIXEL * v_dist) / corr_dist;
		wall_height_and_orientation(data, &vars);
		vars.texture_x = (int)(vars.hitPos * vars.wall_img->width) \
			% vars.wall_img->width;
		pixel_puter(&vars, data);
	}
}

void	draw_rays(t_data *data)
{
	t_raycast	vars;

	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	raycaster_loop(vars, data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
