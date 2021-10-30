#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

t_parser	*init_parser(t_shell *shell)
{
	t_parser	*ret;

	ret = (t_parser *)ft_malloc(sizeof(t_parser), &shell->to_free);
	if (!ret)
		ft_malloc_error(shell->to_free);
	ret->d_quote = 0;
	ret->s_quote = 0;
	return ((t_parser *)ret);
}

t_parser	init_parser_nml(void)
{
	t_parser	ret;

	ret.d_quote = 0;
	ret.s_quote = 0;
	return (ret);
}

t_cmd	*init_cmd(t_shell *shell)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	ret->next = NULL;
	ret->in = NULL;
	ret->out = NULL;
	ret->value = NULL;
	ret->quotes = 0;
	ret->shell = shell;
	return (ret);
}

t_index	init_index(void)
{
	t_index	ret;

	ret.i = 0;
	ret.j = 0;
	ret.k = 0;
	return (ret);
}
