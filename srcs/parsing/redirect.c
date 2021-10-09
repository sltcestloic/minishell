#include "minishell.h"

int	is_redirect(char *str, int *i)
{
	if (str[*i] == '>')
	{
		(*i)++;
		if (str[*i] + 1 == '>')
		{
				(*i)++;
			return (2);
		}
		return (1);
	}
	else if (str[*i] == '<')
	{
		(*i)++;
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
	while (1)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

int	redirect_addback(t_redirect *redirect, int type)
{
	t_redirect	*tmp;

	tmp = redirect_last(redirect);
	tmp->next = malloc(sizeof(t_redirect));
	if (!tmp->next)
		return (0);
	tmp->next->variation = type == 2 || type == 4;
	tmp->next->next = NULL;
	return (1);
}

// < makefile cat

// > = 1 | >> = 2 | < = 3 | << = 4

int	init_redirect_io(t_cmd *cmd, int type)
{
	t_redirect	*redirect;

	if (type < 3)
	{
		if (!cmd->out)
			cmd->out = malloc(sizeof(t_redirect));
		redirect = cmd->out;
	}
	else
	{
		if (!cmd->in)
			cmd->in = malloc(sizeof(t_redirect));
		redirect = cmd->in;
	}
	if (!redirect)
 		return 0;
	//printf("addback (redirect=%p)\n", redirect);
	return (redirect_addback(redirect, type));
}

void	init_redirect(t_cmd *cmd, int type)
{
	int	ret;

	printf("init type=%d\n", type);
	ret = init_redirect_io(cmd, type);
	if (!ret)
	{
		cmd_free(cmd); //TODO free correctement
		return ;
	}
	printf("in=%p out=%p\n", cmd->in, cmd->out);
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