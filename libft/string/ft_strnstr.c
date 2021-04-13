/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 11:09:52 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/01 14:56:47 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	is_to_find(const char *str, const char *to_find, size_t r)
{
	size_t	i;

	i = 0;
	if (r < ft_strlen(to_find))
		return (0);
	while (i < r && to_find[i])
	{
		if (to_find[i] != str[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	int		i;
	int		fsize;

	i = 0;
	if (!str)
		fsize = str[-1];
	fsize = ft_strlen(to_find);
	if (!to_find)
		return ((char *)str);
	if (ft_strlen(str) < len)
		len = ft_strlen(str) + 1;
	while (i <= (int)len)
	{
		if (is_to_find(&str[i], to_find, len - i))
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
