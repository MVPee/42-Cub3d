/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_unit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:07:42 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/09 16:13:57 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void free_data(t_data *data)
{
    //ft_free_matrix(2, &data->map, &data->file);
}

bool init_data(t_data *data)
{
    data->north_image = NULL;
    data->south_image = NULL;
    data->west_image = NULL;
    data->east_image = NULL;
    data->file = NULL;
    data->map = NULL;
    data->image = NULL;
    data->mlx = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, false);
    if (!data->mlx)
		return (true);
    data->player = (t_player_pos *)malloc(sizeof(t_player_pos));
    if (!data->player)
        return (true);
    data->player->x = 0;
    data->player->y = 0;
    data->player->angle = 0;
    data->wall_dir = -1;
    return (false);
}
