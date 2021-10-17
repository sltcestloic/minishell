#include "minishell.h"

char	*get_env_var(t_shell *shell, char *name)
{
	t_envlst	*lst;
	char		*ret;

	lst = shell->env_var;
	printf("%s\n", name);
	if (ft_strcmp(name, "$?") == 0)
		return (ft_itoa(shell->last_exit_return));
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
