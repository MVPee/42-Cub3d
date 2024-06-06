/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:06:22 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/04/15 10:06:22 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../srcs/libft/includes/libft.h"
# include <stdio.h>
# include <errno.h>
# include <stdbool.h>

typedef struct s_data
{
    char *north;
    char *south;
    char *west;
    char *east;

    int *floor;
    int *ceiling;

    char **file;
    char **map;
}   t_data;

// PARSING
bool check_extension(char *str);
bool check_file(t_data *data);
bool check_map(char **map);
void get_new_map(char **map);

#endif