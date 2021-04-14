#include "../libft.h"

char	*ft_malloc(int size, t_free **to_free)
{
	char *ptr;
	t_free *elem;

	ptr = malloc(size);
	elem = malloc(sizeof(t_free));
	if (elem == 0)
	{
		if (ptr != 0)
			free(ptr);
		return (0);
	}
	elem->data = ptr;
	elem->next = *to_free;
	*to_free = elem;
	return (ptr);
}

void	ft_free(t_free **to_free)
{
	t_free *ptr;

	ptr = *to_free;
	while (*to_free)
	{
		free(ptr->data);
		ptr = ptr->next;
		free(*to_free);
		*to_free = ptr;
	}
}

void	ft_free_one(t_free **to_free)
{
	t_free *ptr;

	ptr = *to_free;
	if (*to_free)
	{
		free(ptr->data);
		ptr = ptr->next;
		free(*to_free);
		*to_free = ptr;
	}
}