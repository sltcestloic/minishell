#include "minishell.h"

static void	substitute_env_vars(t_cmd *cmd)
{
	(void)cmd;
	return ;
}

static void	substitute_quotes(t_cmd *cmd)
{
	t_index idx;
	char	*new_value;

	idx.i = 0;
	idx.j = 0;
	idx.k = 0;
	while (cmd->value[idx.i])
	{
		new_value = malloc(sizeof(char) * (ft_strlen(cmd->value[idx.i]) + 1));
		if (!new_value)
			return ; //TODO exit ?
		while (cmd->value[idx.i][idx.j])
		{
			printf("%c\n", cmd->value[idx.i][idx.j]);
			if (cmd->value[idx.i][idx.j] != '\'' && cmd->value[idx.i][idx.j] != '"')
			{
				printf("new_value[%d] = %c\n", idx.k, cmd->value[idx.i][idx.j]);
				new_value[idx.k++] = cmd->value[idx.i][idx.j];
			}
			new_value[idx.k] = 0;
			idx.j++;
		}
		free(cmd->value[idx.i]);
		cmd->value[idx.i] = new_value;
		idx.i++;
		idx.j = 0;
		idx.k = 0;
	}
}

void	substitute(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		substitute_env_vars(cmd);
		substitute_quotes(cmd);
		tmp = tmp->next;
	}
}