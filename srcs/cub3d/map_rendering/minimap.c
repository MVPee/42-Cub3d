/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:46:41 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/10 22:46:53 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

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
    int white = get_rgba(255, 255, 255, 50);
    uint32_t transparent_white = get_correct_color((u_int8_t *)&(white));

    if (data->minimap)
        mlx_delete_image(data->mlx, data->minimap);

    data->minimap = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);

    for (int i = -4; i <= 4; i++)
    { 
        for (int j = -4; j <= 4; j++)
        {
            map_x = (int)data->player->x / PIXEL + i;
            map_y = (int)data->player->y / PIXEL + j;
            if (map_x >= 0 && map_x < data->map_width && map_y >= 0 && map_y < data->map_height && ft_ischarin(data->map[map_y][map_x], "NSWE0"))
                draw_square(data->minimap, 5 + MINIMAP_SIZE / 2 + i * WALL_SIZE, 5 + MINIMAP_SIZE / 2 + j * WALL_SIZE, WALL_SIZE, transparent_white);
        }
    }
    draw_square(data->minimap, 5 + (MINIMAP_SIZE / 2 - PLAYER_SIZE / 2) + 10, (5 + MINIMAP_SIZE / 2 - PLAYER_SIZE / 2) + 10, PLAYER_SIZE, white);
    mlx_image_to_window(data->mlx, data->minimap, WIDTH - MINIMAP_SIZE - 25, 25);
}