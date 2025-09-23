/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 05:52:41 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/09/22 15:09:54 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strlen_2d(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	while (s1[y] == ' ')
		y++;
	while (i < n && s1[y] == s2[i] && s1[y] && s2[i])
	{
		y++;
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[y] - (unsigned char)s2[i]);
}
