/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 06:23:42 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/07/30 16:15:51 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_count(char const *str, char c)
{
	int	count;
	int	init;

	count = 0;
	init = 0;
	while (*str)
	{
		if (*str != c && init == 0)
		{
			init = 1;
			count++;
		}
		else if (*str == c)
			init = 0;
		str++;
	}
	return (count);
}

static char	*ft_copy(char *str, int start, int end)
{
	char	*word;
	int		len;

	len = end - start;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, &str[start], len + 1);
	return (word);
}

static void	ft_free(char **result, int j)
{
	while (j >= 0)
	{
		free(result[j]);
		j--;
	}
	free(result);
}

static char	**process_string(char const *s, char c, char **result)
{
	int i, (j), (start);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (start < i)
		{
			result[j] = ft_copy((char *)s, start, i);
			if (!result[j])
			{
				ft_free(result, j - 1);
				return (NULL);
			}
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = ft_count(s, c);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (process_string(s, c, result));
}
