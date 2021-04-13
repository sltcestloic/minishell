/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:21:23 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/01 14:56:07 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	get_w_start(const char *str, char c, int index)
{
	int	i;

	i = index;
	while (str[i] != c)
	{
		if (i == 0)
		{
			i = -1;
			break ;
		}
		i--;
	}
	i += 1;
	return (i);
}

char	*ft_strrdup(const char *str, int start, int end)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * (end - start + 2));
	if (!ret)
		return (NULL);
	while (start <= end)
	{
		ret[i] = str[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

void	free_split(char **ret)
{
	size_t	i;

	i = 0;
	while (ret[i])
		free(ret[i++]);
	free(ret);
}

int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(const char *str, char c)
{
	char	**ret;
	int		i;
	int		wc;

	i = -1;
	wc = 0;
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!ret)
		return (NULL);
	while (str[++i])
	{
		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
		{
			ret[wc] = ft_strrdup(str, get_w_start(str, c, i), i);
			if (!ret[wc++])
			{
				free_split(ret);
				return (NULL);
			}
		}
	}
	ret[wc] = 0;
	return (ret);
}
