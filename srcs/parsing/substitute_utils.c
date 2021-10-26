#include "minishell.h"

int	is_non_removable(t_parser *parser, char c)
{
	if (c != '\'' && c != '"')
		return (1);
	else if (c == '\'' && parser->d_quote)
		return (1);
	else if (c == '"' && parser->s_quote)
		return (1);
	else
		return (0);
}
