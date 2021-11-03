#include "minishell.h"

t_redirect	*redirect_last(t_redirect *redirect)
{
	t_redirect	*tmp;

	tmp = redirect;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	redirect_addback(t_redirect *redirect, int type, t_shell *shell)
{
	t_redirect	*tmp;

	tmp = redirect_last(redirect);
	tmp->next = (t_redirect *)ft_malloc(sizeof(t_redirect), &shell->to_free);
	if (!tmp->next)
		ft_malloc_error(shell->to_free);
	tmp->next->variation = type == 2 || type == 4;
	tmp->next->next = NULL;
	return (1);
}
