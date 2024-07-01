/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:53 by nechaara          #+#    #+#             */
/*   Updated: 2024/07/01 14:14:17 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	is_wall(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x / PIXEL;
	map_y = (int)y / PIXEL;
	if (map_x < 0 || map_x >= (int)data->map_width || map_y < 0
		|| map_y >= (int)data->map_height)
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
}

static void	move_player_left_right(t_data *data, char c, float *temp_x,
		float *temp_y)
{
	if (c == 'A')
	{
		*temp_x = data->player->x + SPEED * sin(data->player->angle * RADIANT);
		*temp_y = data->player->y + SPEED * -1 * cos(data->player->angle
				* RADIANT);
	}
	else if (c == 'D')
	{
		*temp_x = data->player->x + SPEED * -1 * sin(data->player->angle
				* RADIANT);
		*temp_y = data->player->y + SPEED * cos(data->player->angle * RADIANT);
	}
}

static void	move_player(t_data *data, char c)
{
	float	temp_x;
	float	temp_y;
	float	speed;

	temp_x = data->player->x;
	temp_y = data->player->y;
	speed = SPEED;
	if (data->keys[MLX_KEY_SHIFT])
		speed = SPEED * 2;
	if (c == 'Z')
	{
		temp_x = data->player->x + speed * sin((data->player->angle + 90)
				* RADIANT);
		temp_y = data->player->y + speed * -1 * cos((data->player->angle + 90)
				* RADIANT);
	}
	else if (c == 'S')
	{
		temp_x = data->player->x + speed * -1 * sin((data->player->angle + 90)
				* RADIANT);
		temp_y = data->player->y + speed * cos((data->player->angle + 90)
				* RADIANT);
	}
	move_player_left_right(data, c, &temp_x, &temp_y);
	is_wall(data, temp_x, temp_y);
}

static void door(t_data *data)
{
	int y;
	int x;
	int pos[2];

	pos[0] = (int)data->player->y/PIXEL;
	pos[1] = (int)data->player->x/PIXEL;
	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == 'O')
			{
				data->map[y][x] = 'D';
				if (y == pos[0] && x == pos[1])
					data->map[y][x] = 'O';
				if (y + 1 == pos[0] && x == pos[1])
					data->map[y][x] = 'O';
				if (y - 1 == pos[0] && x == pos[1])
					data->map[y][x] = 'O';
				if (y == pos[0] && x + 1 == pos[1])
					data->map[y][x] = 'O';
				if (y == pos[0] && x - 1 == pos[1])
					data->map[y][x] = 'O';
			}
		}
	}
	if (pos[0] > 0 && pos[0] < (int)data->map_height && pos[1] > 0 &&pos[1] < (int)data->map_width)
	{
		if (data->map[pos[0] + 1][pos[1]] == 'D')
		{
			data->map[pos[0] + 1][pos[1]] = 'O';
			play_sound("rsrcs/sounds/door.mp3");
		}
		if (data->map[pos[0] - 1][pos[1]] == 'D')
		{
			data->map[pos[0] - 1][pos[1]] = 'O';
			play_sound("rsrcs/sounds/door.mp3");
		}
		if (data->map[pos[0]][pos[1] + 1] == 'D')
		{
			data->map[pos[0]][pos[1] + 1] = 'O';
			play_sound("rsrcs/sounds/door.mp3");
		}
		if (data->map[pos[0]][pos[1] - 1] == 'D')
		{
			data->map[pos[0]][pos[1] - 1] = 'O';
			play_sound("rsrcs/sounds/door.mp3");
		}
	}
}

static void copy_image_to_image(t_img *src, t_img *dst)
{
    for (int y = 0; y < src->height; y++)
    {
        for (int x = 0; x < src->width; x++)
        {
            int rgba = get_correct_color(&((u_int8_t *)src->pixels)[(y * src->width + x) * 4]);
            mlx_put_pixel(dst, x, y, rgba);
        }
    }
}

static void fire(t_data *data)
{
    static int count = 0;
    static int frame = 0;
    static bool in = false;
	t_img *current_weapon;
	
	current_weapon = data->weapon[0];
    if (count > 20 || in)
    {
        if (data->keys[MLX_KEY_SPACE] || in)
        {
            in = true;
            if (frame == 0)
            {
                play_sound("rsrcs/sounds/shot.mp3");
                current_weapon = data->weapon[0];
            }
            else if (frame == 1)
            {
                printf("2\n");
                current_weapon = data->weapon[1];
            }
            else if (frame == 2)
            {
                printf("3\n");
                current_weapon = data->weapon[2];
            }
            else if (frame == 3)
            {
                printf("4\n");
                current_weapon = data->weapon[3];
            }
            else if (frame == 4)
            {
                printf("5\n");
                current_weapon = data->weapon[4];
                in = false;
                count = 0;
                frame = -1;
            }
            frame++;
        }
    }
	copy_image_to_image(current_weapon, data->weapon_img);
    count++;
}

void	move_keyhook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->keys[MLX_KEY_Z])
		move_player(data, 'Z');
	if (data->keys[MLX_KEY_S])
		move_player(data, 'S');
	if (data->keys[MLX_KEY_Q])
		move_player(data, 'A');
	if (data->keys[MLX_KEY_D])
		move_player(data, 'D');
	if (data->keys[MLX_KEY_RIGHT])
		rotate_player(data, 'R');
	if (data->keys[MLX_KEY_LEFT])
		rotate_player(data, 'L');
	raycasting(data);
	fire(data);
	minimap(data);
	door(data);
}
