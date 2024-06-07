/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:53 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/07 16:12:10 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void    rotate_player(t_data *data, uint16_t keycode)
{
    
}

void    move_player(t_data *data, uint16_t keycode)
{
    
}

void    move_keyhook(mlx_key_data_t keydata, void *param)
{
    t_data * working_data;
    
    if (!param)
        return ;
    working_data = (t_data *) param;
    printf("keycode %d\n", keydata.key);
    /*
    if (keydata.key == MLX_KEY_Z && (keydata.action == MLX_REPEAT
        || keydata.action == (MLX_PRESS)))
        working_data.p->y += 0.5f;
    else if (keydata.key == MLX_KEY_S && (keydata.action == (MLX_REPEAT)
        || keydata.action == (MLX_PRESS)))
        current_pos->y -= 0.5f;
    else if (keydata.key == MLX_KEY_Q && (keydata.action == (MLX_REPEAT)
        || keydata.action == (MLX_PRESS)))
        current_pos->x -= 0.5f;
    else if (keydata.key == MLX_KEY_D && (keydata.action == (MLX_REPEAT)
        || keydata.action == (MLX_PRESS)))
        current_pos->x += 0.5f;
    */
    //printf("current_pos x : %lf\n current_pos y %lf\n",current_pos->x, current_pos->y);
}