/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_unit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:07:42 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/08 22:12:41 by nechaara         ###   ########.fr       */
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
    data->mlx = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, true);
    if (!data->mlx)
		return (true);
    data->player = (t_player_pos *)malloc(sizeof(t_player_pos));
    if (!data->player)
        return (true);
    data->player->x = 0;
    data->player->y = 0;
    data->player->angle = 0;
    return (false);
}
