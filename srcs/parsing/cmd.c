#include "minishell.h"

void	add_new_cmd(t_cmd *cmd)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->next = NULL;
	new_cmd->in = NULL;
	new_cmd->out = NULL;
	if (!new_cmd)
	{
		cmd_free(cmd); //TODO free correctement
		return ;
	}
	cmd_last(cmd)->next = new_cmd;
}