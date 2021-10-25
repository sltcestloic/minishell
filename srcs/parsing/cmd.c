#include "minishell.h"

void	add_new_cmd(t_cmd *cmd)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->next = NULL;
	new_cmd->in = NULL;
	new_cmd->out = NULL;
	new_cmd->value = NULL;
	if (!new_cmd)
	{
		cmd_free(cmd);
		return ;
	}
	cmd_last(cmd)->next = new_cmd;
}

static char	*next_word(char *input, t_shell *shell)
{
	t_parser	parser;
	char		*ret;
	int			i;

	i = 0;
	parser.d_quote = 0;
	parser.s_quote = 0;
	while (input[i])
	{
		if (input[i] == '"' && !parser.s_quote)
			parser.d_quote = !parser.d_quote;
		else if (input[i] == '\'' && !parser.d_quote)
			parser.s_quote = !parser.s_quote;
		else if (ft_iswhitespace(input[i])
			&& !parser.s_quote && !parser.d_quote)
			break ;
		i++;
	}
	ret = ft_strrdup(input, 0, i - 1, shell->to_free);
	return (ret);
}

/*
** return la taille du mot ajouté au parser pour qu'il passe a la suite
*/
int	add_arg(t_cmd *cmd, char *input, t_shell *shell)
{
	char	**new_value;
	int		i;

	new_value = malloc(sizeof(char *) * (ft_splitlen(cmd->value) + 2));
	i = 0;
	if (!new_value)
		return (-1);
	while (cmd->value[i])
	{
		new_value[i] = ft_strdup(cmd->value[i], shell->to_free);
		free(cmd->value[i]);
		i++;
	}
	new_value[i] = next_word(input, shell);
	new_value[i + 1] = 0;
	free(cmd->value);
	cmd->value = new_value;
	return (ft_strlen(cmd->value[i]) - 1);
}
