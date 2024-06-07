/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:53 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/07 18:48:32 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void    rotate_player(t_data *data, t_mlx_key keydata)
{
    
}

static void compute_coordinates(t_pos *new_coords, t_pos old_cords, double rad, bool is_sub)
{
	
}
void    move_player(t_data *data, t_mlx_key keydata)
{
	t_pos	new_pos;
	t_pos	old_pos;
	double	radiant;
	double	map_max_x;
	double	map_max_y;
	
	map_max_x = (double) data->map_height;
	map_max_y = (double) data->map_width;
	old_pos = data->player->position;
	if (keydata.key == MLX_KEY_Z && (keydata.action == MLX_REPEAT
		|| keydata.action == (MLX_PRESS)))
		compute_coordinates(&new_pos,old_pos, radiant, false);
	else if (keydata.key == MLX_KEY_S && (keydata.action == (MLX_REPEAT)
		|| keydata.action == (MLX_PRESS)))
		compute_coordinates(&new_pos,old_pos, radiant, true);
	else if (keydata.key == MLX_KEY_Q && (keydata.action == (MLX_REPEAT)
		|| keydata.action == (MLX_PRESS)))
		compute_coordinates(&new_pos,old_pos, radiant, true);
	else if (keydata.key == MLX_KEY_D && (keydata.action == (MLX_REPEAT)
		|| keydata.action == (MLX_PRESS)))
		compute_coordinates(&new_pos,old_pos, radiant, false);
	if ((new_pos.x >= 0 && new_pos.x <= map_max_x) && (new_pos.y >= 0 && new_pos.y <= map_max_y))
	{
		data->player->position.x = new_pos.x;
		data->player->position.y = new_pos.y;
	}
}

void    move_keyhook(t_mlx_key keydata, void *param)
{
    t_data *data;
    
    if (!param)
        return ;
    data = (t_data *) param;
	printf("current_pos x : %lf\n current_pos y %lf\n", data->player->position.x, data->player->position.y);
	if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
		rotate_player(data, keydata);
	else
		move_player(data, keydata);
}