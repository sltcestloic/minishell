#include "minishell.h"

t_redirect	*redirect_last(t_redirect *redirect)
{
	t_redirect	*tmp;

	tmp = redirect;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	redirect_addback(t_redirect *redirect, int type)
{
	t_redirect	*tmp;

	tmp = redirect_last(redirect);
	tmp->next = malloc(sizeof(t_redirect));
	if (!tmp->next)
		return (0);
	tmp->next->variation = type == 2 || type == 4;
	tmp->next->next = NULL;
	return (1);
}
