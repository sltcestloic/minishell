#include "minishell.h"

char	*get_env_var(t_shell *shell, char *name)
{
	t_envlst	*lst;
	char		*ret;

	lst = shell->env_var;
	ret = NULL;
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
			return (ft_strdup(lst->value));
		lst = lst->next;
	}
	return (ret);
}
