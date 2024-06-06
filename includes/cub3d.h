/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:18:10 by mvpee             #+#    #+#             */
/*   Updated: 2024/06/06 11:18:10 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../srcs/libft/includes/libft.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_data
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		*floor;
	int		*ceiling;
	char	**file;
	char	**map;
}	t_data;

// PARSING
bool	check_extension(char *str);
bool	check_file(t_data *data);
bool	check_map(char **map);
void	get_new_map(char **map);

#endif
