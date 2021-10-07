#include "minishell.h"

int	is_redirect(char *str, int *i)
{
	if (str[*i] == '>')
	{
		if (str[*i] + 1 == '>')
		{
			(*i)++;
			return (2);
		}
		return (1);
	}
	else if (str[*i] == '<')
	{
		if (str[*i] + 1 == '<')
		{
			(*i)++;
			return (4);
		}
		return (3);
	}
	return (0);
}

t_redirect	*redirect_last(t_redirect *redirect)
{
	t_redirect	*tmp;

	tmp = redirect;
	while (redirect->next)
		redirect = redirect->next;
	return (redirect);
}

void	redirect_addback(t_redirect *redirect, int type)
{
	t_redirect	*tmp;

	tmp = redirect_last(redirect);
	tmp->next = malloc(sizeof(t_redirect));
	tmp->next->variation = type == 2 || type == 4;
	if (!tmp->next)
		exit(1); //TODO free correctement
}

// < makefile cat

// > = 1 | >> = 2 | < = 3 | << = 4

void	init_redirect(t_cmd *cmd, int type)
{
	t_redirect *redirect;
	if (type < 3)
		redirect = cmd->out;
	else
		redirect = cmd->in;
	if (redirect)
	{
		redirect_addback(redirect, type);
		return ;
	}
	redirect = malloc(sizeof(t_redirect));
	redirect->variation = type == 2 || type == 4;
	if (!redirect)
	{
		cmd_free(cmd); //TODO free correctement
		return ;
	}
}

void	set_file_name(t_redirect *redirect, char *input, int *i)
{
	int	j;

	j = 0;
	while (ft_iswhitespace(input[*i]))
		(*i)++;
	while (ft_isalnum(input[*i]))
	{
		(*i)++;
		j++;
	}
	redirect->file_name = malloc(sizeof(char) * (j + 1));
	if (!redirect->file_name)
		exit(1); //TODO free correctement
	*i -= j;
	j = 0;
	while (ft_isalnum(input[*i]))
		redirect->file_name[j++] = input[(*i)++];
	redirect->file_name[j] = '\0';
}