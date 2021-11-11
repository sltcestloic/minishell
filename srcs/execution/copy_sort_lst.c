#include "minishell.h"

int	size_list(t_envlst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**lst_to_str(t_shell *shell)
{
	char		**ret;
	char		*save;
	t_envlst	*lst;
	int			i;

	i = 0;
	lst = shell->env_var;
	ret = malloc(sizeof(char *) * size_list(lst) + 1);
	if (!ret)
		return (NULL);
	while (lst)
	{
		ret[i] = ft_strdup(lst->name, shell->to_free);
		save = ft_strjoin(lst->name, "=", shell->to_free);
		ret[i] = ft_strjoin(save, lst->value, shell->to_free);
		lst = lst->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

static inline void	swap_elem(t_envlst *elem1, t_envlst *elem2)
{
	char		*value;
	char		*name;

	value = elem1->value;
	name = elem1->name;
	elem1->value = elem2->value;
	elem1->name = elem2->name;
	elem2->value = value;
	elem2->name = name;
}

static inline void	sort_lst(t_envlst *sorted)
{
	t_envlst	*ptr;

	while (sorted->next)
	{
		ptr = sorted->next;
		while (ptr)
		{
			if (ft_strcmp(sorted->name, ptr->name) > 0)
				swap_elem(sorted, ptr);
			ptr = ptr->next;
		}
		sorted = sorted->next;
	}
}

static inline t_envlst	*copy_elem(t_envlst *lst)
{
	t_envlst	*new;

	new = malloc(sizeof(t_envlst));
	if (!new)
		return (0);
	new->next = 0;
	new->value = lst->value;
	new->name = lst->name;
	return (new);
}

t_envlst	*copy_sorted_list(t_envlst *lst)
{
	t_envlst	*sorted;
	t_envlst	*ptr;

	if (!lst->next)
		return (lst);
	sorted = copy_elem(lst);
	ptr = sorted;
	while (lst->next)
	{
		ptr->next = copy_elem(lst->next);
		ptr = ptr->next;
		lst = lst->next;
	}
	sort_lst(sorted);
	return (sorted);
}
