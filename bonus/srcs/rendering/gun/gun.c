/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:41:25 by mvpee             #+#    #+#             */
/*   Updated: 2024/07/02 20:39:55 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	copy_image_to_image(t_img *src, t_img *dst)
{
	int	rgba;
	int	x;
	int	y;

	y = -1;
	while (++y < src->height)
	{
		x = -1;
		while (++x < src->width)
		{
			rgba = get_correct_color(&((u_int8_t *)src->pixels)[(y * src->width
						+ x) * 4]);
			mlx_put_pixel(dst, x, y, rgba);
		}
	}
}

static void	fire(t_data *data, bool *in, int *count, t_img **current_weapon)
{
	static int	frame = 0;

	*in = true;
	if (frame == 0)
	{
		play_sound("rsrcs/sounds/shot.mp3");
		*current_weapon = data->weapon[0];
	}
	else if (frame == 1)
		*current_weapon = data->weapon[1];
	else if (frame == 2)
		*current_weapon = data->weapon[2];
	else if (frame == 3)
		*current_weapon = data->weapon[3];
	else if (frame == 4)
	{
		*current_weapon = data->weapon[4];
		*in = false;
		*count = 0;
		frame = -1;
	}
	frame++;
}

void	gun(t_data *data)
{
	static int	count = 0;
	static bool	in = false;
	t_img		*current_weapon;

	current_weapon = data->weapon[0];
	if (count++ > GUN_SPEED || in)
		if (data->keys[MLX_KEY_SPACE] || in)
			fire(data, &in, &count, &current_weapon);
	copy_image_to_image(current_weapon, data->weapon_img);
}
