/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:46:41 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/13 09:30:34 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool is_in_cercle(int x, int y)
{
    int dx = x - MINIMAP_SIZE / 2;
    int dy = y - MINIMAP_SIZE / 2;
    return (dx * dx + dy * dy) < (MINIMAP_SIZE / 2) * (MINIMAP_SIZE / 2);
}

static void draw_square(mlx_image_t *img, int x, int y, int size, uint32_t color)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (x + j >= 0 && x + j < img->width && y + i >= 0 && y + i < img->height)
                mlx_put_pixel(img, x + j, y + i, color);
}

void mini_map(t_data *data)
{
    int map_x;
    int map_y;
    uint32_t transparent_white = get_rgba(255, 255, 255, 50);
    uint32_t white = get_rgba(255, 255, 255, 255);
    uint32_t transparent = get_rgba(0, 0, 0, 0);
    uint32_t black = get_rgba(0, 0, 0, 255);
    uint32_t black2 = get_rgba(0, 0, 0, 100);
    
    transparent_white = get_correct_color((u_int8_t *)&(transparent_white));
    black = get_correct_color((u_int8_t *)&(black));
    black2 = get_correct_color((u_int8_t *)&(black2));
    transparent = get_correct_color((u_int8_t *)&(transparent));
    
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
            mlx_put_pixel(data->minimap, j, i, black2);
    for (int i = (MINIMAP_SIZE/40 + 1) * - 1; i <= (MINIMAP_SIZE/40 + 1); i++)
    { 
        for (int j = (MINIMAP_SIZE/40 + 1) * - 1; j <= (MINIMAP_SIZE/40 + 1); j++)
        {
            map_x = (int)data->player->x / PIXEL + i;
            map_y = (int)data->player->y / PIXEL + j;
            if (map_x >= 0 && map_x < data->map_width && map_y >= 0 && map_y < data->map_height && ft_ischarin(data->map[map_y][map_x], "NSWE0"))
                draw_square(data->minimap, x_adjust + MINIMAP_SIZE / 2 + i * WALL_SIZE, y_adjust + MINIMAP_SIZE / 2 + j * WALL_SIZE, WALL_SIZE, transparent_white);
        }
    }
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
    draw_square(data->minimap, 5 + (MINIMAP_SIZE / 2 - PLAYER_SIZE / 2), (5 + MINIMAP_SIZE / 2 - PLAYER_SIZE / 2), PLAYER_SIZE, white);
    mlx_image_to_window(data->mlx, data->minimap, WIDTH - MINIMAP_SIZE - 25, 25);
}
