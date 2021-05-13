#include "minishell.h"

void	cmd_addback(t_cmd *cmd, t_cmd *add)
{
	t_cmd	*current;

	current = cmd;
	while (1)
	{
		if (!current->next)
			break ;
		current = current->next;
	}
	current->next = add;
}

void	cmd_addfront(t_cmd *cmd, t_cmd *add)
{
	add->next = cmd;
	cmd = add;
}

void	cmd_free(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->value)
			free_split(current->value);
		free(current);
		current = current->next;
	}
	free(current);
}
