/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:53 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/15 22:34:27 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	is_wall(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x / PIXEL;
	map_y = (int)y / PIXEL;
	if (map_x < 0 || map_x >= data->map_width || map_y < 0
		|| map_y >= data->map_height)
		return ;
	if (data->map[(int)data->player->y / PIXEL][((int)x + PIXEL / 8)
		/ PIXEL] == '1')
		x = data->player->x;
	if (data->map[((int)y + PIXEL / 8) / PIXEL][(int)data->player->x
		/ PIXEL] == '1')
		y = data->player->y;
	if (data->map[(int)data->player->y / PIXEL][((int)x - PIXEL / 8)
		/ PIXEL] == '1')
		x = data->player->x;
	if (data->map[((int)y - PIXEL / 8) / PIXEL][(int)data->player->x
		/ PIXEL] == '1')
		y = data->player->y;
	if (data->map[(int)data->player->y / PIXEL][(int)x / PIXEL] != '1')
		data->player->x = x;
	if (data->map[(int)y / PIXEL][(int)data->player->x / PIXEL] != '1')
		data->player->y = y;
}

static void	rotate_player(t_data *data, char c)
{
	if (c == 'R')
        data->player->angle += SPEED_ROTATION;
    else if (c == 'L')
        data->player->angle -= SPEED_ROTATION;
    if (data->player->angle >= 360)
        data->player->angle -= 360;
    else if (data->player->angle < 0)
        data->player->angle += 360;
    printf(BLUE "\nPlayer Rotation:\n\t%d°\n" RESET, data->player->angle);
}

static void    move_player(t_data *data, char c)
{
    float    temp_x;
    float    temp_y;

    if (c == 'A')
    {
        temp_x = data->player->x + SPEED * sin(data->player->angle * RADIANT);
        temp_y = data->player->y + SPEED * -1 * cos(data->player->angle
                * RADIANT);
    }
    else if (c == 'D')
    {
        temp_x = data->player->x + SPEED * -1 * sin(data->player->angle
                * RADIANT);
        temp_y = data->player->y + SPEED * cos(data->player->angle * RADIANT);
    }
    else if (c == 'S')
    {
        temp_x = data->player->x + SPEED * -1 * sin((data->player->angle + 90)
                * RADIANT);
        temp_y = data->player->y + SPEED * cos((data->player->angle + 90)
                * RADIANT);
    }
    else if (c == 'Z')
    {
        temp_x = data->player->x + SPEED * sin((data->player->angle + 90)
                * RADIANT);
        temp_y = data->player->y + SPEED * -1 * cos((data->player->angle + 90)
                * RADIANT);
    }
    is_wall(data, temp_x, temp_y);
}

static void	movement(t_data *data)
{
	if (data->keys[MLX_KEY_Z])
        move_player(data, 'Z');
    if (data->keys[MLX_KEY_S]) // Reculer
        move_player(data, 'S');
    if (data->keys[MLX_KEY_Q]) // Tourner à gauche
        move_player(data, 'A');
    if (data->keys[MLX_KEY_D]) // Tourner à droite
        move_player(data, 'D');
    if (data->keys[MLX_KEY_RIGHT]) // Déplacer vers la droite
        rotate_player(data, 'R');
    if (data->keys[MLX_KEY_LEFT]) // Déplacer vers la gauche
        rotate_player(data, 'L');
}

void	move_keyhook(void *param)
{
	t_data *data;

	data = (t_data *)param;
	draw_rays(data);
	minimap(data);
	movement(data);
}
