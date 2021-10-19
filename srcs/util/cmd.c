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

void	free_reditects(t_cmd *cmd)
{
	t_redirect	*current;
	t_redirect	*tmp;

	current = cmd->in;
	while (current)
	{
		if (current->file_name)
			free(current->file_name);
		tmp = current->next;
		free(current);
		current = tmp;
	}
	current = cmd->out;
	while (current)
	{
		if (current->file_name)
			free(current->file_name);
		tmp = current->next;
		free(current);
		current = tmp;
	}
}

void	cmd_free(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = cmd;
	while (current)
	{
		free_reditects(current);
		if (current->value)
			free_cmd_value(current->value);
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free(current);
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