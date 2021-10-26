#include "minishell.h"

void	cmd_bzero(t_cmd *cmd, int args)
{
	int	i;

	i = 0;
	cmd->value = malloc(sizeof(char *) * args);
	while (i < args)
		cmd->value[i++] = 0;
}

void	quote_cmd(t_parser *parser, char c)
{
	if (c == '"' && !parser->s_quote)
		parser->d_quote = !parser->d_quote;
	else if (c == '\'' && !parser->d_quote)
		parser->s_quote = !parser->s_quote;
}

int	is_sep(char c)
{
	return (c == '>' || c == '<' || c == '|' || ft_iswhitespace(c));
}
