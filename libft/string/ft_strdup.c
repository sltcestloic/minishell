/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 14:37:10 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/18 09:26:55 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *src, t_free *to_free)
{
	char	*dest;

	dest = ft_malloc(sizeof(char) * ft_strlen(src) + 1, &to_free);
	if (!dest)
		ft_malloc_error(to_free);
	if (src)
	{
		ft_strlcpy(dest, (char *)src, ft_strlen(src) + 1);
	}
	return (dest);
}

char	*ft_strdup_g(const char *src)
{
	char	*dest;

	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	if (src)
	{
		ft_strlcpy(dest, (char *)src, ft_strlen(src) + 1);
	}
	return (dest);
}
