#include "minishell.h"

/*
*	idx.j = quotes before
*	idx.k = char before
*/
static char	*substitute_env_var(t_shell *shell, char *input,
	int var, t_index idx)
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
	while (input[i] && !is_sep(input[i])
		&& (!is_quote(input[i]) || input[i] == '?' || i == var))
		i++;
	var_name = ft_strrdup(input, var + 1, i - 1, shell->to_free);
	new_var = get_env_var(shell, var_name, idx.j, idx.k);
	ret = ft_strjoin(ret, new_var, shell->to_free);
	if ((int)ft_strlen(input) > i)
	{
		end = ft_strrdup(input, i, ft_strlen(input) - 1, shell->to_free);
		ret = ft_strjoin(ret, end, shell->to_free);
	}
	if (!idx.j && ft_strlen(ret) == 0)
		ret = (char *)1;
	return (ret);
}

void	substitute_env_vars(t_shell *shell, t_cmd *cmd)
{
	t_index	idx;
	t_index	var;
	char	*tmp;

	idx.i = 0;
	idx.j = 0;
	while (cmd->value[idx.i])
	{
		var = has_env_var(cmd->value[idx.i], shell);
		idx.k = var.i;
		if (idx.k != -1)
		{
			tmp = substitute_env_var(shell, cmd->value[idx.i], idx.k, idx);
			cmd->value[idx.i] = tmp;
			continue ;
		}
		idx.i++;
	}
}
