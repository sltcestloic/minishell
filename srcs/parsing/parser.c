/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:21:25 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/16 14:33:36 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_name(char *input)
{
	char	*ret;
	char	**split;
	int		i;

	i = 0;
	if (*input)
	{
		split = ft_split(input, ' ');	
		ret = malloc(sizeof(char) * (ft_strlen(split[0]) + 1));
		while (split[0][i])
		{
			ret[i] = split[0][i];
			i++;
		}
		ret[i] = '\0';
		free_split(split);
	}
	else
		return (input);
	return (ret);
}

char	**get_command_args(char	*input)
{
	char	**ret;
	char	**split;
	int		i;

	i = 1;
	if (!*input)
		return (NULL);
	split = ft_split(input, ' ');
	ret = malloc(sizeof(char *) * ft_splitlen(split));
	while (split[i])
	{
		ret[i - 1] = ft_strdup(split[i]);
		i++;
	}
	ret[i - 1] = 0;
	free_split(split);
	return (ret);
}

t_command	parse_command(char *input)
{
	t_command	cmd;

	cmd.name = get_command_name(input);
	cmd.args = get_command_args(input);
	return (cmd);
}

// void	parse_input(char *input, t_shell *shell)
// {
	
// }

// void	handle_cmd(char *input)
// {
// 	t_command	cmd;

// 	cmd = parse_command(input);
// 	if (ft_strcmp("exit", cmd.name) == 0)
// 		ft_exit(shell->to_free);
// 	else if (ft_strcmp("echo", cmd.name) == 0)
// 		parse_echo(&cmd);
// 	else if (ft_strcmp("env", cmd.name) == 0)
// 		env(shell->env_var);
// 	else if (ft_strcmp("export", cmd.name) == 0)
// 		export(shell->env_var);
// 	free(cmd.name);
// 	if (cmd.args)
// 		free_split(cmd.args);
// }
