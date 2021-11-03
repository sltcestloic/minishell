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
	add->next = NULL;
	current->next = add;
}

void	free_cmd_value(char **value)
{
	size_t	i;

	i = 0;
	while (value[i])
		free(value[i++]);
	free(value);
}

t_cmd	*cmd_last(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (1)
	{
		if (!current->next)
			break ;
		current = current->next;
	}
	return (current);
}
