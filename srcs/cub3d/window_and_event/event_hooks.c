/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:53 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/09 19:39:09 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int is_wall(t_data *data, float x, float y)
{
    int map_x = (int)x / PIXEL;
    int map_y = (int)y / PIXEL;

    if (map_x < 0 || map_x >= data->map_width || map_y < 0 || map_y >= data->map_height)
        return 1;
    if ((int)data->player->y/PIXEL != map_y || (int)data->player->x/PIXEL != map_x)
        if (data->map[map_y][map_x] != '1')
            if (data->map[map_y][(int)data->player->x/PIXEL] == '1' || data->map[(int)data->player->y/PIXEL][map_x] == '1')
                return (1);
    return (data->map[map_y][map_x] == '1');
}

static void rotate_player(t_data *data, t_mlx_key keydata)
{
    if (keydata.key == MLX_KEY_RIGHT)
        data->player->angle += SPEED_ROTATION;
    else if(keydata.key == MLX_KEY_LEFT)
        data->player->angle -= SPEED_ROTATION;
    if (data->player->angle >= 360)
        data->player->angle -= 360;
    else if (data->player->angle < 0)
        data->player->angle += 360;
    printf(BLUE "\nPlayer Rotation:\n\t%d°\n" RESET, data->player->angle);
}

void    move_player(t_data *data, t_mlx_key keydata)
{
	float temp_x;
	float temp_y;

	if (keydata.key == 256) // ESCAP
        exit(0);
	if (keydata.key == MLX_KEY_Z && (keydata.action == MLX_REPEAT || keydata.action == (MLX_PRESS)))
	{
        temp_x = data->player->x + SPEED * sin(data->player->angle * RADIANT);
        temp_y = data->player->y + SPEED * -1 * cos(data->player->angle * RADIANT);
        if (!is_wall(data, temp_x, temp_y))
        {
            data->player->x = temp_x;
            data->player->y = temp_y;
        }
    }
	else if (keydata.key == MLX_KEY_S && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
	{
        temp_x = data->player->x + SPEED * -1 * sin(data->player->angle * RADIANT);
        temp_y = data->player->y + SPEED * cos(data->player->angle * RADIANT);
        if (!is_wall(data, temp_x, temp_y))
        {
            data->player->x = temp_x;
            data->player->y = temp_y;
        }
    }
    else if (keydata.key == MLX_KEY_A && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
	{
        temp_x = data->player->x + SPEED * -1 * sin((data->player->angle + 90) * RADIANT);
        temp_y = data->player->y + SPEED * cos((data->player->angle + 90) * RADIANT);
        if (!is_wall(data, temp_x, temp_y))
        {
            data->player->x = temp_x;
            data->player->y = temp_y;
        }
    }
    else if (keydata.key == MLX_KEY_D && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
	{
        temp_x = data->player->x + SPEED * sin((data->player->angle + 90) * RADIANT);
        temp_y = data->player->y + SPEED * -1 * cos((data->player->angle + 90) * RADIANT);
        if (!is_wall(data, temp_x, temp_y))
        {
            data->player->x = temp_x;
            data->player->y = temp_y;
        }
    }
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
		rotate_player(data, keydata);
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
		rotate_player(data, keydata);
	draw_rays(data);
}

void    move_keyhook(t_mlx_key keydata, void *param)
{
    t_data *data;
    
    if (!param)
        return ;
    data = (t_data *) param;
	move_player(data, keydata);
}