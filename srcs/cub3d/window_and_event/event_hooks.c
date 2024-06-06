/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:53 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/06 14:37:03 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void move_keyhook(mlx_key_data_t keydata, void *param)
{
	t_pos	*current_pos;
	
	if (!param)
		return ;
	current_pos = (t_pos *) param;
	if (keydata.key == MLX_KEY_Z && keydata.action == (MLX_REPEAT))
		current_pos->y += 0.5f;
	if (keydata.key == MLX_KEY_S && keydata.action == (MLX_REPEAT))
		current_pos->y -= 0.5f;
	if (keydata.key == MLX_KEY_Q && keydata.action == (MLX_REPEAT))
		current_pos->x -= 0.5f;
    if (keydata.key == MLX_KEY_D && keydata.action == (MLX_REPEAT))
		current_pos->x += 0.5f;
	printf("current_pos x : %lf\n current_pos y %lf\n",current_pos->x, current_pos->y);
}
