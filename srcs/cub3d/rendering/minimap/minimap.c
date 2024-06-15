/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:46:41 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/15 17:41:57 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/cub3d.h"

static bool is_in_cercle(int x, int y)
{
    int dx;
    int dy;

    dy = y - MINIMAP_SIZE / 2;
    dx = x - MINIMAP_SIZE / 2;
    return (dx * dx + dy * dy) < (MINIMAP_SIZE / 2) * (MINIMAP_SIZE / 2);
}

static void draw_square(t_minimap *minimap, int x, int y, char c)
{
    int color;
    int size;
    
    if (c == 'P')
    {
        color = minimap->white;
        size = PLAYER_SIZE;
    }
    else if (c == 'W')
    {
        color = minimap->transparent_white;
        size = WALL_SIZE;
    }
    else
        return;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (x + j >= 0 && x + j < MINIMAP_SIZE && y + i >= 0 && y + i < MINIMAP_SIZE)
                minimap->map_input[x + j][y + i] = color;
}

static void rotateImage(t_minimap *minimap, double radians)
{
    double cosAngle;
    double sinAngle;
    int newX;
    int newY;

    cosAngle = cos(radians);
    sinAngle = sin(radians);
    for (int y = 0; y < MINIMAP_SIZE; y++)
        for (int x = 0; x < MINIMAP_SIZE; x++)
            minimap->map_output[y][x] = 0;
    for (int y = 1; y < MINIMAP_SIZE; y++)
    {
        for (int x = 1; x < MINIMAP_SIZE; x++)
        {
            newX = (int)((x - MINIMAP_SIZE / 2) * cosAngle - (y - MINIMAP_SIZE / 2) * sinAngle + MINIMAP_SIZE / 2);
            newY = (int)((x - MINIMAP_SIZE / 2) * sinAngle + (y - MINIMAP_SIZE / 2) * cosAngle + MINIMAP_SIZE / 2);
            if (newX >= 0 && newX < MINIMAP_SIZE && newY >= 0 && newY < MINIMAP_SIZE)
                minimap->map_output[newY][newX] = minimap->map_input[y][x];
        }
    }
    for (int y = 1; y < MINIMAP_SIZE; y++)
    {
        for (int x = 1; x < MINIMAP_SIZE; x++)
        {
            if (minimap->map_output[y][x] == minimap->transparent)
            {
                minimap->map_output[y][x] = minimap->map_output[y - 1][x];
                if (minimap->map_output[y][x] == minimap->transparent)
                    minimap->map_output[y][x] = minimap->map_output[y][x - 1];
            }
        }
    }
}

void minimap(t_data *data)
{
    int map_x;
    int map_y;
    
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

    if (data->minimap->image)
        mlx_delete_image(data->mlx, data->minimap->image);
    data->minimap->image = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);

    for (int i = 0; i < MINIMAP_SIZE; i++)
        for (int j = 0; j < MINIMAP_SIZE; j++)
            data->minimap->map_input[i][j] = data->minimap->transparent_black;
    for (int i = (MINIMAP_SIZE/40 + 1) * - 1; i <= (MINIMAP_SIZE/40 + 1); i++)
    { 
        for (int j = (MINIMAP_SIZE/40 + 1) * - 1; j <= (MINIMAP_SIZE/40 + 1); j++)
        {
            map_x = (int)data->player->x / PIXEL + i;
            map_y = (int)data->player->y / PIXEL + j;
            if (map_x >= 0 && map_x < data->map_width && map_y >= 0 && map_y < data->map_height && ft_ischarin(data->map[map_y][map_x], "NSWE0"))
                draw_square(data->minimap, x_adjust + MINIMAP_SIZE / 2 + i * WALL_SIZE, y_adjust + MINIMAP_SIZE / 2 + j * WALL_SIZE, 'W');
        }
    }
    draw_square(data->minimap, 5 + (MINIMAP_SIZE / 2 - PLAYER_SIZE / 2), (5 + MINIMAP_SIZE / 2 - PLAYER_SIZE / 2), 'P');
    rotateImage(data->minimap, (data->player->angle + 90) * RADIANT);
    for (int i = 0; i < MINIMAP_SIZE; i++)
        for (int j = 0; j < MINIMAP_SIZE; j++)
            mlx_put_pixel(data->minimap->image, i, j, data->minimap->map_output[i][j]);

    
    for (int i = 0; i < MINIMAP_SIZE; i++)
    {
        for (int j = 0; j < MINIMAP_SIZE; j++)
        {
            if (!is_in_cercle(j - 1, i) || !is_in_cercle(j + 1, i) || !is_in_cercle(j, i - 1) || !is_in_cercle(j, i + 1))
                mlx_put_pixel(data->minimap->image, j, i, data->minimap->black);
            if (!is_in_cercle(j, i))
                mlx_put_pixel(data->minimap->image, j, i, data->minimap->transparent);   
        }
    }
    mlx_image_to_window(data->mlx, data->minimap->image, WIDTH - MINIMAP_SIZE - 25, 25);
}
