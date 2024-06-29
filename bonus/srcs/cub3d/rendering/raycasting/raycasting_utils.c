/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@19.be>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:59:10 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/29 08:30:44 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/cub3d.h"

static void	compute_dist(t_distance *vars, t_data *data, float *hit_x,
		float *hit_y)
{
	float	p_x;
	float	p_y;

	p_x = data->player->x;
	p_y = data->player->y;
	if ((int)vars->prev_y / PIXEL != (int)vars->y / PIXEL && !((int)vars->prev_x
			/ PIXEL != (int)vars->x / PIXEL))
	{
		if (vars->prev_y < vars->y)
			data->wall_dir = 'S';
		else
			data->wall_dir = 'N';
	}
	else if ((int)vars->prev_x / PIXEL != (int)vars->x / PIXEL
		&& !((int)vars->prev_y / PIXEL != (int)vars->y / PIXEL))
	{
		if (vars->prev_x < vars->x)
			data->wall_dir = 'E';
		else
			data->wall_dir = 'W';
	}
	vars->distance = sqrt(pow(vars->x - p_x, 2) + pow(vars->y - p_y, 2));
	*hit_x = vars->x;
	*hit_y = vars->y;
}

float	get_distance(t_data *data, float rotation, float *hit_x, float *hit_y)
{
	t_distance	vars;

	vars.prev_x = 0;
	vars.prev_y = 0;
	vars.x = data->player->x;
	vars.y = data->player->y;
	vars.angle_rad = rotation * RADIANT;
	vars.step_x = cos(vars.angle_rad);
	vars.step_y = sin(vars.angle_rad);
	while ((int)vars.y / PIXEL < (int)data->map_height && (int)vars.x \
		/ PIXEL < (int)data->map_width && \
		data->map[(int)vars.y / PIXEL][(int)vars.x / PIXEL] != '1' && \
		data->map[(int)vars.y / PIXEL][(int)vars.x / PIXEL] != 'D')
	{
		vars.prev_x = vars.x;
		vars.prev_y = vars.y;
		vars.x += vars.step_x;
		vars.y += vars.step_y;
	}
	compute_dist(&vars, data, hit_x, hit_y);
	if (data->map[(int)vars.y / PIXEL][(int)vars.x / PIXEL] == 'D')
		data->door = 1;
	return (vars.distance);
}
