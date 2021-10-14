#include "minishell.h"

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
	//printf("args: %d\n", result);
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
	printf("cmd->value[%d] = 0\n", args + 1);
	if (!cmd->value)
		return (0);
	while (input[*i] && input[*i] != '|' && !ft_iswhitespace(input[*i]))
	{
		(*i)++;
		idx.i++;
	}
	cmd->value[0] = ft_strrdup(input, *i - idx.i, *i - 1);
	//printf("cmd->value[0] = %s\n", cmd->value[0]);
	while (ft_iswhitespace(input[*i]))
		(*i)++;
	idx.i = *i;
	while (input[*i])
	{
		if (input[*i] == '"' && !parser.s_quote)
		{
			parser.d_quote = !parser.d_quote;
			//printf("dquote: %d\n", parser.d_quote);
		}
		else if (input[*i] == '\'' && !parser.d_quote)
		{
			parser.s_quote = !parser.s_quote;
			//printf("squote: %d\n", parser.d_quote);
		}
		//printf("char=%c inquote=%d\n", input[*i], parser.s_quote || parser.d_quote);
		if (!parser.s_quote && !parser.d_quote)
		{
			if (is_sep(input[*i]))
			{
				(*i)--; //pour que parse_input puisse lire le | et ajouter une cmd
				break;
			}
			if (ft_iswhitespace(input[*i + 1]) || !input[*i + 1])
			{
				cmd->value[idx.j++] = ft_strrdup(input, idx.i, *i);
				//printf("cmd->value[%d] = %s\n", idx.j - 1, cmd->value[idx.j - 1]);
				idx.i = *i + 1;
				while (ft_iswhitespace(input[idx.i]))
					idx.i++;
				*i = idx.i - 1;
				//printf("%d=%c\n", idx.i + 1, input[idx.i + 1]);
			}
		}
		(*i)++;
	}
	(*i)--;
	//printf("%d %d\n", idx.i, *i - 1);
	if (idx.i < *i)
	{
		cmd->value[idx.j++] = ft_strrdup(input, idx.i, *i - 1);
		//printf("cmd->value[%d] = %s\n", idx.j - 1, cmd->value[idx.j - 1]);
	}
	return (1);
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
		if (!parser->s_quote && !parser->d_quote)
		{
			parser->redirect = is_redirect(input, &i);
			if (parser->redirect)
			{
				printf("redirect: %d\n", parser->redirect);
				init_redirect(cmd_last(cmd), parser->redirect);
				if (parser->redirect < 3)
				{
					printf("set out\n");
					set_file_name(cmd_last(cmd)->out, input, &i);
				}
				else
				{
					printf("set in\n");
					set_file_name(cmd_last(cmd)->in, input, &i);
				}
				continue ;
			}
			else if (input[i] == '|')
				add_new_cmd(cmd);
		}
		if (ft_isalnum(input[i]))
		{
			//printf("call set content (%c,%d)\n", input[i], i);
			if (!set_cmd_content(cmd_last(cmd), input, &i))
			{
				cmd_free(cmd); //TODO free correctement
				exit(0);
			}
		}
		else if (input[i] == '"' && !parser->s_quote)
			parser->d_quote = !parser->d_quote;
		else if (input[i] == '\'' == !parser->d_quote)
			parser->s_quote = !parser->s_quote;
		//printf("%d\n", i);
		i++;
	}
	if (parser->d_quote || parser->s_quote)
		printf("Invalid input: unclosed quote.\n");
	else
	{
		substitute(cmd);
		/* DEBUG START */
		int count = 0;
		//t_cmd *tmp = cmd;
		while (cmd)
		{
			printf("----------cmd #%d----------\n", count);
			for (int n = 0; cmd->value[n]; n++)
				printf("cmd->value[%d] = %s\n", n, cmd->value[n]);
				int k = 0;
			if (cmd->in)
			{
				printf(" redirect in:\n");
				while (cmd->in)
				{
					printf("  redirect #%d:\n", k);
					printf("   cmd->in->file_name = %s\n", cmd->in->file_name);
					printf("   cmd->in->variation = %d\n", cmd->in->variation);
					k++;
					cmd->in = cmd->in->next;
				}
			}
			if (cmd->out)
			{
				printf(" redirect out:\n");
				k = 0;
				
				while (cmd->out)
				{
					printf("  redirect #%d:\n", k);
					printf("   cmd->out->file_name = %s\n", cmd->out->file_name);
					printf("   cmd->out->variation = %d\n", cmd->out->variation);
					k++;
					cmd->out = cmd->out->next;
				}
			}
			cmd = cmd->next;
			count++;
		}
		//cmd_parse(tmp, shell);
		/* DEBUG END */
	}
	// printf("end parser\n");
	// free(parser);
	// printf("parser freed\n");
	// cmd_free(cmd);
	// printf("cmd freed\n");
}
