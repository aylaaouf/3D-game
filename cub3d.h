/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 05:53:14 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/21 08:31:51 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include <string.h>
# include <unistd.h>

// parsing
int     parser(int ac, char **av);
int     has_cub_extension(char *path);

// utils
char	*ft_strrchr(const char *s, int c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
size_t  ft_strlen(const char *s);
void	ft_putendl_fd(char *s, int fd);

#endif