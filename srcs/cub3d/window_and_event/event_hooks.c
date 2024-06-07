/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:53 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/07 19:56:59 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void    rotate_player(t_data *data, t_mlx_key keydata)
{
    if (keydata.key == MLX_KEY_RIGHT)
		data->player->degree += 15;
	else if(keydata.key == MLX_KEY_LEFT)
		data->player->degree -= 15;
	if (data->player->degree > 360)
		data->player->degree %= 360;
	else if (data->player->degree < 0)
		data->player->degree += 360;
	printf("Degree:\t%d\n", data->player->degree);
}

static void check_border(t_data *data, float temp_x, float temp_y)
{
	if (data->player->y + temp_y > 0 && data->player->y + temp_y < ft_splitlen((const char **)data->map))
		data->player->y += temp_y;
	if (data->player->x + temp_x > 0 && data->player->x + temp_x < ft_strlen(data->map[(int)data->player->y]))
		data->player->x += temp_x;
	if (data->map[(int)data->player->y + 1][(int)data->player->x + 1] == '1')
	{
		data->player->y -= temp_y;
		data->player->x -= temp_x;
	}
}

void    move_player(t_data *data, t_mlx_key keydata)
{
	float temp_x;
	float temp_y;

	if (keydata.key == MLX_KEY_Z && (keydata.action == MLX_REPEAT || keydata.action == (MLX_PRESS)))
	{
		temp_x = SPEED * sin(data->player->degree * RADIANT);
		temp_y = SPEED * -1 * cos(data->player->degree * RADIANT);
		check_border(data, temp_x, temp_y);
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
	{
		temp_x = SPEED * -1 * sin(data->player->degree * RADIANT);
		temp_y = SPEED * cos(data->player->degree * RADIANT);
		check_border(data, temp_x, temp_y);
	}
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
		rotate_player(data, keydata);
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
		rotate_player(data, keydata);
}

void    move_keyhook(t_mlx_key keydata, void *param)
{
    t_data *data;
    
    if (!param)
        return ;
    data = (t_data *) param;
	move_player(data, keydata);
}