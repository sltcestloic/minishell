#include "minishell.h"

<<<<<<< HEAD
/* void	handle_cmd(char **input, t_shell *shell)
{
	int	i;

	i = 1;
	if (ft_strcmp("exit", input[0]) == 0)
		ft_exit(shell->to_free);
	else if (ft_strcmp("echo", input[0]) == 0)
		parse_echo(input);
	else if (ft_strcmp("env", input[0]) == 0)
		env(shell->env_var);
	else if (ft_strcmp("unset", input[0]) == 0)
	{
		while (input[i])
		{
			remove_env_elem(input[i], shell);
			i++;
		}
	}
	else if (ft_strcmp("export", input[0]) == 0)
	{
		if (!input[1])
			export(shell->env_var);
		else
		{
			while (input[i])
			{
				new_env_elem(input[i], shell);
				i++;
			}
		}
	}
	else if (ft_strcmp("cd", input[0]) == 0)
	{
		if (!input[0])
			change_pwd(shell, 0);
		else if (ft_splitlen(input) > 2)
			write(1, "cd: too many arguments\n", 24);
		else
			change_pwd(shell, input[0]);
	}
	else if (ft_strcmp("pwd", input[0]) == 0)
		pwd(shell);
	else
		to_exec(shell, input);
	free(input);
} */

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

=======
>>>>>>> 0df85e84781b5e680b34c12afcfd208710e101c3
int	is_sep(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int		count_args(char *input)
{
	t_parser	parser;
	int			i;
	int			result;

	parser.s_quote = 0;
	parser.d_quote = 0;
	i = 0;
	result = 0;
	while (input[i])
	{
		if (ft_iswhitespace(input[i]) && !ft_iswhitespace(input[i + 1]) && !parser.s_quote && !parser.d_quote)
			result++;
		else if (input[i] == '"' && !parser.s_quote)
			parser.d_quote = !parser.d_quote;
		else if (input[i] == '\'' && !parser.d_quote)
			parser.s_quote = !parser.s_quote;
		else if (is_sep(input[i]))
		{
			if (i > 0 && ft_iswhitespace(input[i - 1]))
				result--;
			break ;
		}
		i++;
	}
	return (result);
}

int	set_cmd_content(t_cmd *cmd, char *input, int *i)
{
	t_index		idx;
	t_parser	parser;
	int			args;

	idx.i = 0;
	idx.j = 1;
	parser.s_quote = 0;
	parser.d_quote = 0;
	args = count_args(&input[*i]);
	cmd->value = malloc(sizeof(char *) * (args + 2));
	cmd->value[args + 1] = 0;
	// printf("cmd->value[%d] = 0\n", args + 1);
	if (!cmd->value)
		return (0);
	while (input[*i] && input[*i] != '|' && !ft_iswhitespace(input[*i]))
	{
		(*i)++;
		idx.i++;
	}
	cmd->value[0] = ft_strrdup(input, *i - idx.i, *i - 1);
	while (ft_iswhitespace(input[*i]))
		(*i)++;
	idx.i = *i;
	while (input[*i])
	{
		if (input[*i] == '"' && !parser.s_quote)
		{
			parser.d_quote = !parser.d_quote;
		}
		else if (input[*i] == '\'' && !parser.d_quote)
			parser.s_quote = !parser.s_quote;
		if (!parser.s_quote && !parser.d_quote)
		{
			if (is_sep(input[*i]))
			{
				(*i)--;
				break;
			}
			if (ft_iswhitespace(input[*i + 1]) || !input[*i + 1])
			{
				cmd->value[idx.j++] = ft_strrdup(input, idx.i, *i);
				idx.i = *i + 1;
				while (ft_iswhitespace(input[idx.i]))
					idx.i++;
				*i = idx.i - 1;
			}
		}
		(*i)++;
	}
	(*i)--;
	if (idx.i < *i)
		cmd->value[idx.j++] = ft_strrdup(input, idx.i, *i - 1);
	return (1);
}

void	print_struct_debug(t_cmd *cmd)
{
	t_cmd *tmp = cmd;
	int count = 0;
	while (tmp)
	{
		printf("----------cmd #%d----------\n", count);
		for (int n = 0; tmp->value[n]; n++)
			printf("cmd->value[%d] = |%s|\n", n, tmp->value[n]);
			int k = 0;
		if (tmp->in)
		{
			printf(" redirect in:\n");
			while (tmp->in)
			{
				printf("  redirect #%d:\n", k);
				printf("   cmd->in->file_name = %s\n", tmp->in->file_name);
				printf("   cmd->in->variation = %d\n", tmp->in->variation);
				k++;
				tmp->in = tmp->in->next;
			}
		}
		if (tmp->out)
		{
			printf(" redirect out:\n");
			k = 0;	
			while (tmp->out)
			{
				printf("  redirect #%d:\n", k);
				printf("   cmd->out->file_name = %s\n", tmp->out->file_name);
				printf("   cmd->out->variation = %d\n", tmp->out->variation);
				k++;
				tmp->out = tmp->out->next;
			}
		}
		tmp = tmp->next;
		count++;
	}
}

void	parse_input(char *input, t_shell *shell)
{
	t_cmd		*cmd;
	int			i;
	t_parser	*parser;

	(void)shell;
	parser = init_parser();
	i = 0;
	cmd = init_cmd();
	while (input[i]) {
		parser->redirect = is_redirect(input, &i);
		if (parser->redirect)
		{
			init_redirect(cmd_last(cmd), parser->redirect);
			if (parser->redirect < 3)
				set_file_name(cmd_last(cmd)->out, input, &i);
			else
				set_file_name(cmd_last(cmd)->in, input, &i);
			continue ;
		}
		else if (input[i] == '|')
			add_new_cmd(cmd);
		else if (ft_isalnum(input[i]))
		{
			if (cmd_last(cmd)->value)
			{
				printf("%s\n", cmd_last(cmd)->value[0]);
				if (input[i - 1] == '\'' || input[i - 1] == '"')
				{
					i += add_arg(cmd_last(cmd), &input[i - 1]);
					parser->d_quote = 0;
					parser->s_quote = 0;
				}
				else
					i += add_arg(cmd_last(cmd), &input[i]);
			}
			else if (!set_cmd_content(cmd_last(cmd), input, &i))
			{
				cmd_free(cmd); //TODO free correctement
				exit(0);
			}
		}
		i++;
	}
	int sub = substitute(shell, cmd);
	print_struct_debug(cmd);
	if (sub)
		cmd_parse(cmd, shell);
	// printf("end parser\n");
	// free(parser);
	// printf("parser freed\n");
	// cmd_free(cmd);
	// printf("cmd freed\n");
}
