/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:16:29 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/11 09:16:29 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void *play_mp3(void)
{
	pid_t music;

	// while(1)
	// {
	music = fork();
	if (music == 0)
		execlp("mpg123", "mpg123", "rsrcs/sounds/music.mp3", NULL);
	//waitpid(music, NULL, 0);
	// }
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	*temp;

	temp = NULL;
	if (ac != 2)
		return (ft_printf_fd(2, RED NUMBERS_OF_ARGUMENTS RESET), 1);
	if (init_data(&data))
		return (ft_printf_fd(2, RED WIN_INIT_FAILED RESET), 1);
	if (check_extension(av[1]))
		return (free_data(&data), 1);
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
	//pthread_create(&data.thread, NULL, play_mp3, NULL);
	play_sound("rsrcs/sounds/music.mp3");
	if (game_loop(&data))
		return (free_data(&data), 1);
	return (free_data(&data), 0);
}
