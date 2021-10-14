#include "minishell.h"

char	*get_env_var(t_shell *shell, char *name)
{
	t_envlst	*lst;
	char		*ret;

	lst = shell->env_var;
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
			return (ft_strdup(lst->value));
		lst = lst->next;
	}
	ret = malloc(1);
	*ret = 0;
	return (ret);
}
