/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:53 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/14 16:53:17 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void is_wall(t_data *data, float x, float y)
{
    int map_x;
    int map_y;

    map_x = (int)x / PIXEL;
    map_y = (int)y / PIXEL;
    if (map_x < 0 || map_x >= data->map_width || map_y < 0 || map_y >= data->map_height)
        return;
    if (data->map[(int)data->player->y / PIXEL][((int)x + PIXEL / 8) / PIXEL] == '1')
        x = data->player->x;
    if (data->map[((int)y + PIXEL / 8) / PIXEL][(int)data->player->x / PIXEL] == '1')
        y = data->player->y;
    if (data->map[(int)data->player->y / PIXEL][((int)x - PIXEL / 8) / PIXEL] == '1')
        x = data->player->x;
    if (data->map[((int)y - PIXEL / 8) / PIXEL][(int)data->player->x / PIXEL] == '1')
        y = data->player->y;
    if (data->map[(int)data->player->y / PIXEL][(int)x / PIXEL] != '1')
        data->player->x = x;
    if (data->map[(int)y / PIXEL][(int)data->player->x / PIXEL] != '1')
        data->player->y = y;
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

static void move_player(t_data *data, t_mlx_key keydata)
{
    float temp_x;
    float temp_y;

    if (keydata.key == MLX_KEY_A)
    {
        temp_x = data->player->x + SPEED * sin(data->player->angle * RADIANT);
        temp_y = data->player->y + SPEED * -1 * cos(data->player->angle * RADIANT);
    }
    else if (keydata.key == MLX_KEY_D)
    {
        temp_x = data->player->x + SPEED * -1 * sin(data->player->angle * RADIANT);
        temp_y = data->player->y + SPEED * cos(data->player->angle * RADIANT);
    }
    else if (keydata.key == MLX_KEY_S)
    {
        temp_x = data->player->x + SPEED * -1 * sin((data->player->angle + 90) * RADIANT);
        temp_y = data->player->y + SPEED * cos((data->player->angle + 90) * RADIANT);
    }
    else if (keydata.key == MLX_KEY_Z)
    {
        temp_x = data->player->x + SPEED * sin((data->player->angle + 90) * RADIANT);
        temp_y = data->player->y + SPEED * -1 * cos((data->player->angle + 90) * RADIANT);
    }
    is_wall(data, temp_x, temp_y);
}

static void    movement(t_data *data, t_mlx_key keydata)
{
	if (keydata.key == MLX_KEY_ESCAPE)
        exit(0); //free
	if ((keydata.key == MLX_KEY_Z || \
        keydata.key == MLX_KEY_S || \
        keydata.key == MLX_KEY_A || \
        keydata.key == MLX_KEY_D ) && \
        (keydata.action == MLX_REPEAT || keydata.action == (MLX_PRESS)))
        move_player(data, keydata);
	else if (keydata.key == MLX_KEY_RIGHT && \
        (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
		rotate_player(data, keydata);
    else if (keydata.key == MLX_KEY_LEFT && \
        (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
		rotate_player(data, keydata);
}

void    move_keyhook(t_mlx_key keydata, void *param)
{
    t_data *data;
    
    if (!param)
        return ;
    data = (t_data *) param;
    movement(data, keydata);
    draw_rays(data);
    mini_map(data);
}