/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:22:06 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/10 21:58:02 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static float calculate_distance_to_wall(t_data *data, float rotation, float *hitX, float *hitY)
{
    float x;
    float y;
    float angle_rad;
    float step_x;
    float step_y;
    int prev_x;
    int prev_y;

    x = data->player->x;
    y = data->player->y;
    angle_rad = rotation * RADIANT;
    step_x = cos(angle_rad);
    step_y = sin(angle_rad);

    while ((int)y / PIXEL < data->map_height && (int)x / PIXEL < data->map_width && data->map[(int)y / PIXEL][(int)x / PIXEL] != '1') 
    {
        prev_x = x;
        prev_y = y;

        x += step_x;
        y += step_y;
    }
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
    float distance = sqrt(pow(x - data->player->x, 2) + pow(y - data->player->y, 2));
    *hitX = x;
    *hitY = y;

    return distance;
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
    float ray_angle;
    float corrected_distance ;
    float view_distance;
    mlx_image_t *wall_img;

    if (data->image)
        mlx_delete_image(data->mlx, data->image);
    data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    rotation = data->player->angle - 90 - ((float) WIDTH / 2) * DEGREE;
    for (int x = 0; x < WIDTH; x++) {
		view_distance = (WIDTH / (2 * tan(((float) FOV/2.0f) * RADIANT)));
		ray_angle = data->player->angle + atan((x - WIDTH / 2.0f) / view_distance) * (180.0f / M_PI);
		distance = calculate_distance_to_wall(data, ray_angle, &hitX, &hitY);
		corrected_distance = distance * cos((ray_angle - data->player->angle) * RADIANT);
        wall_height = (PIXEL * view_distance) / corrected_distance;
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
    //printf(RED"PLAYER X : %d PLAYER Y: %d\n" RESET, (int) data->player->x, (int) data->player->y);
    mlx_image_to_window(data->mlx, data->image, 0, 0);
}
