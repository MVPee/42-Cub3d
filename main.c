/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:53:08 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/04/15 09:53:08 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

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

int main(int ac, char **av)
{
    t_data data;
    char *temp;

    if (ac != 2)
        return (ft_printf_fd(2, RED "Error\nNumber of argument(s)\n" RESET), 1);

    if (init_data(&data))
        return (ft_printf_fd(2, RED "Error\nMLX INIT FAILED\n" RESET), 1);

    // Extension Check
    if (check_extension(av[1]))
        return (free_data(&data), 1);

    // Get file
    if ((temp = ft_read(open(av[1], O_RDONLY))))
        data.file = ft_split(temp, "\n");
    else
        return (free_data(&data), 1);
    ft_free(1, &temp);

    // Check file
    if (check_file(&data))
        return (free_data(&data),1);

    // Check map
    if (check_map(&data.map))
        return (free_data(&data), 1);
    // Display map / settings
    for(int i = 0; i < ft_splitlen((const char **)data.map); i++)
        ft_printf("%d.\t%s\n", i, data.map[i]);

    get_map_size(&data);
	get_player_pos(&data);

	if (game_loop(&data))
		return (free_data(&data), 1);
    return (free_data(&data), 0);
}
