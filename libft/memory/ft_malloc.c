#include "../libft.h"

inline static t_free	*last_elem(t_free *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

char	*ft_malloc(int size, t_free **to_free)
{
	char *ptr;
	t_free *elem;

	ptr = malloc(size);
	elem = malloc(sizeof(t_free));
	if (!elem)
	{
		if (ptr)
			free(ptr);
		return (0);
	}
	elem->data = ptr;
	elem->next = 0;
	if (*to_free)
	{
		*to_free = last_elem(*to_free);
		(*to_free)->next = elem;
	}
	else
		*to_free = elem;
	return (ptr);
}

void	ft_free(t_free *to_free)
{
	t_free *ptr;

	ptr = to_free;
	while (to_free)
	{
		free(ptr->data);
		ptr = ptr->next;
		free(to_free);
		to_free = ptr;
	}
}

void	ft_free_one(t_free **to_free)
{	
	t_free *ptr;
	t_free *save;

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