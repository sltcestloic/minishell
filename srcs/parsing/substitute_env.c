
#include "minishell.h"

char	*substitute_env_var(t_shell *shell, char *input, int var)
{
	char	*ret;
	char	*var_name;
	char	*new_var;
	char	*end;
	int		i;

	ret = NULL;
	if (var > 0)
	{
		ret = ft_strrdup(input, 0, var - 1);
		if (!ret)
			ft_malloc_error(shell->to_free);
	}
	i = var;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '?' || i == var))
		i++;
	var_name = ft_strrdup(input, var + 1, i - 1);
	if (!var_name)
	{
		if (ret)
			free(ret);
		ft_malloc_error(shell->to_free);
	}
	new_var = get_env_var(shell, var_name, var && input[var - 1] == '"');
	if (!new_var)
	{
		if (ret)
			free(ret);
		free(var_name);
		ft_malloc_error(shell->to_free);
	}
	free(var_name);
	ret = ft_strjoin(ret, new_var);
	if (!ret)
	{
		free(var_name);
		free(new_var);
		ft_malloc_error(shell->to_free);
	}
	free(new_var);
	if ((int)ft_strlen(input) > i)
	{
		end = ft_strrdup(input, i, ft_strlen(input) - 1);
		if (!end)
		{
			free(var_name);
			free(ret);
			ft_malloc_error(shell->to_free);
		}
		ret = ft_strjoin(ret, end);
		if (!ret)
		{
			free(var_name);
			free(end);
			ft_malloc_error(shell->to_free);
		}
		free(end);
	}
	return (ret);
}
