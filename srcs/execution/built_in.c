/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:37:18 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/26 15:33:16 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_built_in(t_cmd *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->value[0], "echo"))
		echo(cmd->value);
	else if (!ft_strcmp(cmd->value[0], "env"))
		env(shell->env_var);
	else if (!ft_strcmp(cmd->value[0], "export"))
	{
		if (!cmd->value[1])
			export_cmd(shell->env_var, shell);
		else if (cmd->value[1])
			update_env_value(shell, cmd->value);
	}
	else if (!ft_strcmp(cmd->value[0], "unset"))
		remove_env_elem(cmd->value, shell);
	else if (!ft_strcmp(cmd->value[0], "exit"))
		exit_cmd(shell, cmd->value, 0);
	else if (!ft_strcmp(cmd->value[0], "cd"))
		change_pwd(shell, cmd->value[1]);
	else if (!ft_strcmp(cmd->value[0], "pwd"))
		pwd(shell);
	else
		return (1);
	return (0);
}

int	is_built_in(t_cmd *cmd)
{
	if (!cmd->value)
		return (0);
	else if (!ft_strcmp(cmd->value[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "pwd"))
		return (1);
	else
		return (0);
}

int	redirect_to_built_in(t_cmd *cmd, t_shell *shell)
{
	int	in;
	int	out;
	int	ret;

	in = dup(0);
	out = dup(1);
	ret = 0;
	redirect(cmd, NULL, NULL);
	if (cmd->value)
		ret = do_built_in(cmd, shell);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	return (ret);
}

void	check_built_in(char **func, t_shell *shell)
{
	if (!ft_strcmp(func[0], "echo"))
		echo(func);
	else if (!ft_strcmp(func[0], "env"))
		env(shell->env_var);
	else if (!ft_strcmp(func[0], "export"))
	{
		if (!func[1])
			export_cmd(shell->env_var, shell);
		else if (func[1])
			new_env_elem(func[1], shell);
	}
	else if (!ft_strcmp(func[0], "unset"))
		remove_env_elem(func, shell);
	else if (!ft_strcmp(func[0], "exit"))
		exit_cmd(shell, func, 1);
	else if (!ft_strcmp(func[0], "cd"))
		change_pwd(shell, func[1]);
	else if (!ft_strcmp(func[0], "pwd"))
		pwd(shell);
	else
		return ;
	exit(g_last_exit = 0);
}
