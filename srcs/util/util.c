#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_sep(char c)
{
	return (c == '>' || c == '<' || c == '|' || ft_iswhitespace(c));
}
