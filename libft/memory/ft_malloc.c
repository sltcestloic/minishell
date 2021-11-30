/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:25:58 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/30 12:47:57 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_malloc_error(t_free *to_free)
{
	ft_free(to_free);
	write(2, "Malloc error.\n", 14);
	exit(0);
}

static t_free	*last_elem(t_free *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

char	*ft_malloc(int size, t_free **to_free)
{
	char	*ptr;
	t_free	*elem;

	ptr = malloc(size);
	if (!ptr)
		ft_malloc_error(*to_free);
	*ptr = 0;
	elem = malloc(sizeof(t_free));
	if (!elem)
	{
		if (ptr)
			free(ptr);
		ft_malloc_error(*to_free);
	}
	elem->data = ptr;
	elem->next = 0;
	if (*to_free)
		last_elem(*to_free)->next = elem;
	else
		*to_free = elem;
	return (ptr);
}

void	ft_free(t_free *to_free)
{
	t_free	*ptr;

	ptr = to_free;
	while (to_free)
	{
		printf("free %p\n", ptr->data);
		if (ptr->data)
			free(ptr->data);
		ptr = ptr->next;
		printf("free %p\n", to_free);
		free(to_free);
		to_free = ptr;
	}
}

void	ft_free_one(t_free **to_free)
{	
	t_free	*ptr;
	t_free	*save;

	ptr = *to_free;
	save = 0;
	while (ptr->next)
	{
		save = ptr;
		ptr = ptr->next;
	}
	if (save)
		save->next = 0;
	else
		*to_free = 0;
	free(ptr->data);
	free(ptr);
}
