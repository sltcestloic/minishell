#include "minishell.h"

char	*substitute_env_var(t_shell *shell, char *input, int var, int quotes)
{
	char	*ret;
	char	*var_name;
	char	*new_var;
	char	*end;
	int		i;

	ret = NULL;
	if (var > 0)
		ret = ft_strrdup(input, 0, var - 1, shell->to_free);
	i = var;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '?' || i == var))
		i++;
	var_name = ft_strrdup(input, var + 1, i - 1, shell->to_free);
	new_var = get_env_var(shell, var_name, quotes);
	ret = ft_strjoin(ret, new_var, shell->to_free);
	if ((int)ft_strlen(input) > i)
	{
		end = ft_strrdup(input, i, ft_strlen(input) - 1, shell->to_free);
		ret = ft_strjoin(ret, end, shell->to_free);
	}
	return (ret);
}
