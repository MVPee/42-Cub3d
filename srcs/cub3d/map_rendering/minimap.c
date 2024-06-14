/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:46:41 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/14 17:40:07 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool is_in_cercle(int x, int y)
{
    int dx = x - MINIMAP_SIZE / 2;
    int dy = y - MINIMAP_SIZE / 2;
    return (dx * dx + dy * dy) < (MINIMAP_SIZE / 2) * (MINIMAP_SIZE / 2);
}

static void draw_square(int map[MINIMAP_SIZE][MINIMAP_SIZE], int x, int y, int size, uint32_t color)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (x + j >= 0 && x + j < MINIMAP_SIZE && y + i >= 0 && y + i < MINIMAP_SIZE)
                map[x + j][y + i] = color;
}

void rotateImage(double angle, int input[MINIMAP_SIZE][MINIMAP_SIZE], int output[MINIMAP_SIZE][MINIMAP_SIZE])
{
    int transparent_white = get_rgba(255, 255, 255, 50);
    int white = get_rgba(255, 255, 255, 255);
    int transparent = get_rgba(0, 0, 0, 0);
    int black = get_rgba(0, 0, 0, 255);
    int black2 = get_rgba(0, 0, 0, 100);
    
    transparent_white = get_correct_color((u_int8_t *)&(transparent_white));
    black = get_correct_color((u_int8_t *)&(black));
    black2 = get_correct_color((u_int8_t *)&(black2));
    transparent = get_correct_color((u_int8_t *)&(transparent));
    
    double radians = angle * M_PI / 180.0;
    double cosAngle = cos(radians);
    double sinAngle = sin(radians);

    int x0 = MINIMAP_SIZE / 2;
    int y0 = MINIMAP_SIZE / 2;

    for (int y = 0; y < MINIMAP_SIZE; y++)
        for (int x = 0; x < MINIMAP_SIZE; x++)
            output[y][x] = 0;

    for (int y = 0; y < MINIMAP_SIZE; y++)
    {
        for (int x = 0; x < MINIMAP_SIZE; x++)
        {
            int newX = (int)((x - x0) * cosAngle - (y - y0) * sinAngle + x0);
            int newY = (int)((x - x0) * sinAngle + (y - y0) * cosAngle + y0);
            if (newX >= 0 && newX < MINIMAP_SIZE && newY >= 0 && newY < MINIMAP_SIZE)
                output[newY][newX] = input[y][x];
        }
    }
    for (int y = 1; y < MINIMAP_SIZE - 1; y++)
        for (int x = 1; x < MINIMAP_SIZE - 1; x++)
            if (output[y][x] == transparent)
                output[y][x] = output[y][x - 1];
}


void mini_map(t_data *data)
{
    int map_x;
    int map_y;
    int transparent_white = get_rgba(255, 255, 255, 50);
    int white = get_rgba(255, 255, 255, 255);
    int transparent = get_rgba(0, 0, 0, 0);
    int black = get_rgba(0, 0, 0, 255);
    int black2 = get_rgba(0, 0, 0, 100);
    
    transparent_white = get_correct_color((u_int8_t *)&(transparent_white));
    black = get_correct_color((u_int8_t *)&(black));
    black2 = get_correct_color((u_int8_t *)&(black2));
    transparent = get_correct_color((u_int8_t *)&(transparent));
    
    int map_input[MINIMAP_SIZE][MINIMAP_SIZE];
    int map_output[MINIMAP_SIZE][MINIMAP_SIZE];
    int y_adjust = 0;
    int x_adjust = 0;

    if (data->player->y/128-(int)(data->player->y/128) > 0.25)
        y_adjust = -5;
    if (data->player->y/128-(int)(data->player->y/128) > 0.5)
        y_adjust = -10;
    if (data->player->x/128-(int)(data->player->x/128) > 0.25)
        x_adjust = -5;
    if (data->player->x/128-(int)(data->player->x/128) > 0.5)
        x_adjust = -10;

    if (data->minimap)
        mlx_delete_image(data->mlx, data->minimap);
    data->minimap = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);

    for (int i = 0; i < MINIMAP_SIZE; i++)
        for (int j = 0; j < MINIMAP_SIZE; j++)
            map_input[i][j] = black2;
    for (int i = (MINIMAP_SIZE/40 + 1) * - 1; i <= (MINIMAP_SIZE/40 + 1); i++)
    { 
        for (int j = (MINIMAP_SIZE/40 + 1) * - 1; j <= (MINIMAP_SIZE/40 + 1); j++)
        {
            map_x = (int)data->player->x / PIXEL + i;
            map_y = (int)data->player->y / PIXEL + j;
            if (map_x >= 0 && map_x < data->map_width && map_y >= 0 && map_y < data->map_height && ft_ischarin(data->map[map_y][map_x], "NSWE0"))
                draw_square(map_input, x_adjust + MINIMAP_SIZE / 2 + i * WALL_SIZE, y_adjust + MINIMAP_SIZE / 2 + j * WALL_SIZE, WALL_SIZE, transparent_white);
        }
    }
    draw_square(map_input, 5 + (MINIMAP_SIZE / 2 - PLAYER_SIZE / 2), (5 + MINIMAP_SIZE / 2 - PLAYER_SIZE / 2), PLAYER_SIZE, white);

    rotateImage(data->player->angle + 90, map_input, map_output);
    for (int i = 0; i < MINIMAP_SIZE; i++)
        for (int j = 0; j < MINIMAP_SIZE; j++)
            mlx_put_pixel(data->minimap, i, j, map_output[i][j]);

    for (int i = 0; i < MINIMAP_SIZE; i++)
    {
        for (int j = 0; j < MINIMAP_SIZE; j++)
        {
            if (!is_in_cercle(j - 1, i) || !is_in_cercle(j + 1, i) || !is_in_cercle(j, i - 1) || !is_in_cercle(j, i + 1))
                mlx_put_pixel(data->minimap, j, i, black);
            if (!is_in_cercle(j, i))
                mlx_put_pixel(data->minimap, j, i, transparent);   
        }
    }
    mlx_image_to_window(data->mlx, data->minimap, WIDTH - MINIMAP_SIZE - 25, 25);
}
