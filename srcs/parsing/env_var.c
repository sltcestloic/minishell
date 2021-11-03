#include "minishell.h"

int	count_quotes(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			count++;
		i++;
	}
	return (count);
}

char	*var_value_noquotes(char *var, t_free *to_free)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_malloc(sizeof(char) * (ft_strlen(var)
				+ count_quotes(var) + 1), &to_free);
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '\'' || var[i] == '"')
			ret[j++] = '\\';
		if (var[i] == ' ' && j && ret[j - 1] != ' ')
			ret[j++] = var[i];
		else if (var[i] != ' ')
			ret[j++] = var[i];
		i++;
	}
	if (ret[j - 1] == ' ')
		ret[j - 1] = 0;
	ret[j] = 0;
	return (ret);
}

char	*get_env_var(t_shell *shell, char *name, int quotes)
{
	t_envlst	*lst;
	char		*ret;

	lst = shell->env_var;
	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(shell->last_exit_return));
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			if (quotes)
				return (ft_strdup(lst->value, shell->to_free));
			else
				return (var_value_noquotes(lst->value, shell->to_free));
		}
		lst = lst->next;
	}
	ret = ft_malloc(1, &shell->to_free);
	*ret = 0;
	return (ret);
}

t_index	has_env_var(char *input, t_shell *shell)
{
	t_parser	*parser;
	t_index		idx;

	parser = init_parser(shell);
	idx.i = 0;
	idx.j = 0;
	while (input[idx.i])
	{
		if (input[idx.i] == '"' && !parser->s_quote)
			parser->d_quote = !parser->d_quote;
		else if (input[idx.i] == '\'' && !parser->d_quote)
			parser->s_quote = !parser->s_quote;
		else if (input[idx.i] == '$' && !parser->s_quote)
		{
			idx.j = parser->d_quote || parser->s_quote;
			return (idx);
		}
		idx.i++;
	}
	idx.i = -1;
	return (idx);
}
