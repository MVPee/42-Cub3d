/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:22:06 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/10 09:40:28 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static float calculate_distance_to_wall(t_data *data, float rotation, float *hitX, float *hitY)
{
    float x = data->player->x;
    float y = data->player->y;
    float angle_rad = rotation * RADIANT;
    float prev_x;
    float prev_y;
    int count = 0;

    while ((int)y / PIXEL < data->map_height && (int)x / PIXEL < data->map_width && data->map[(int)y / PIXEL][(int)x / PIXEL] != '1') {
        prev_x = x;
        prev_y = y;

        x += cos(angle_rad);
        y += sin(angle_rad);
        count++;
        if (count > 2000)
            return (-1);
    }
    *hitX = x;
    *hitY = y;
    if ((int)prev_y / PIXEL != (int)y / PIXEL)
    {
        if (prev_y < y)
            data->wall_dir = 'S';
        else
            data->wall_dir = 'N';
    }
    else if ((int)prev_x / PIXEL != (int)x / PIXEL)
    {
        if (prev_x < x)
            data->wall_dir = 'E';
        else
            data->wall_dir = 'W';
    }
    return sqrt(pow(x - data->player->x, 2) + pow(y - data->player->y, 2));
}

void draw_rays(t_data *data)
{
    float distance;
    float rotation;
    float wall_height;
    int texture_x, texture_y;
    float hitX, hitY;
    float hitPos;
    int color;
    int x, y;
    mlx_image_t *wall_img;

    if (data->image)
        mlx_delete_image(data->mlx, data->image);
    data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);

    rotation = data->player->angle - 90 - (WIDTH / 2) * DEGREE;
    for (x = 0; x < WIDTH; x++) {
        distance = calculate_distance_to_wall(data, rotation, &hitX, &hitY);
        wall_height = (PIXEL / distance) * (PIXEL * 5);
        if (wall_height - (int)wall_height > 0.5)
            wall_height += 1;

        if (data->wall_dir == 'E' || data->wall_dir == 'W')
            hitPos = hitY / PIXEL;
        else
            hitPos = hitX / PIXEL;

        if (data->wall_dir == 'N')
            wall_img = data->north_image;
        else if (data->wall_dir == 'S')
            wall_img = data->south_image;
        else if (data->wall_dir == 'E')
            wall_img = data->east_image;
        else if (data->wall_dir == 'W')
            wall_img = data->west_image;

        texture_x = (int)(hitPos * wall_img->width) % wall_img->width;

        if (distance != -1)
        {
            for (y = 0; y < (int)wall_height; y++) {
                texture_y = (y * wall_img->height) / (int)wall_height;
                if (y + (HEIGHT - (int)wall_height) / 2 < data->image->height) {
                    color = get_correct_color(&((u_int8_t *)wall_img->pixels)[(texture_y * wall_img->width + texture_x) * 4]);
                    mlx_put_pixel(data->image, x, (float)y + ((float)HEIGHT - wall_height) / 2, color);
                }
            }
        }

        rotation += DEGREE;
    }
    mlx_image_to_window(data->mlx, data->image, 0, 0);
}
