/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:12:38 by mvpee             #+#    #+#             */
/*   Updated: 2024/07/17 10:12:38 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static bool	ft_check_init(t_data *data, char **av)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, false);
	if (!data->mlx)
		return (ft_printf_fd(2, RED WIN_INIT_FAILED RESET), true);
	if (init_data(data))
		return (ft_printf_fd(2, MALLOC_FAILED RESET), true);
	if (check_extension(av[1]))
		return (free_data(data), true);
	return (false);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	*temp;

	if (ac != 2)
		return (ft_printf_fd(2, RED NUMBERS_OF_ARGUMENTS RESET), 1);
	if (ft_check_init(&data, av))
		return (1);
	temp = ft_read(open(av[1], O_RDONLY));
	data.file = ft_split(temp, "\n");
	if (!data.file)
		return (ft_free(1, &temp), free_data(&data), 1);
	ft_free(1, &temp);
	if (check_file(&data))
		return (free_data(&data), 1);
	if (check_map(&data.map))
		return (free_data(&data), 1);
	get_map_size(&data);
	get_player_pos(&data);
	play_sound("rsrcs/sounds/music.mp3");
	if (game_loop(&data))
		return (free_data(&data), 1);
	return (free_data(&data), 0);
}
