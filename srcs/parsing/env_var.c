#include "minishell.h"

char	*var_value_noquotes(char *var)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char) * (ft_strlen(var) + 1));
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == ' ' && ret[j] != ' ')
			ret[j++] = var[i];
		else if (var[i] != ' ')
			ret[j++] = var[i];
		i++;
	}
	ret[j] = 0;
	return (ret);
}

char	*get_env_var(t_shell *shell, char *name, int quotes)
{
	t_envlst	*lst;
	char		*ret;

	lst = shell->env_var;
	if (ft_strcmp(name, "$?") == 0)
		return (ft_itoa(shell->last_exit_return));
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			if (!quotes)
				return (ft_strdup(lst->value));
			else
				return (var_value_noquotes(lst->value));
		}
		lst = lst->next;
	}
	ret = malloc(1);
	*ret = 0;
	return (ret);
}
