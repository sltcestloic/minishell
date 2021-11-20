/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:49:19 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/19 14:37:55 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd, char *msg, int exit_value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(g_last_exit = exit_value);
}

void	fork_exec(int in, int out, t_cmd *cmd, t_shell *shell)
{
	if (shell->to_close)
		close(shell->to_close);
	if (in)
		if (dup2(in, 0))
			close(in);
	if (out != 1)
		if (dup2(out, 1))
			close(out);
	redirect(cmd);
	if (cmd->value)
		to_exec(shell, cmd->value);
	g_last_exit = 0;
	exit(g_last_exit);
}

void	spawn_proc(int in, int out, t_cmd *cmd, t_shell *shell)
{
	int	pid;
	int	already_sig;

	already_sig = 0;
	unset_term(shell);
	signal(SIGQUIT, signal_reset);
	signal(SIGINT, signal_reset);
	pid = fork();
	if (!pid)
		fork_exec(in, out, cmd, shell);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (out == 1)
	{
		waitpid(pid, &pid, 0);
		g_last_exit = WEXITSTATUS(pid);
		already_sig = signal_handle(pid);
		while (waitpid(-1, &pid, 0) != -1)
			if (!already_sig)
				already_sig = signal_handle(pid);
	}
}

static void	last_cmd(int in, t_cmd *cmd, t_shell *shell)
{
	if (in)
	{
		spawn_proc(in, 1, cmd, shell);
		close(in);
	}
	else if (is_built_in(cmd))
		redirect_to_built_in(cmd, shell);
	else
		spawn_proc(in, 1, cmd, shell);
}

void	cmd_parse(t_cmd *cmd, t_shell *shell)
{
	int	in;
	int	fd[2];

	in = 0;
	if (do_heredoc(cmd) == -1)
		return ;
	while (cmd->next)
	{
		pipe(fd);
		shell->to_close = fd[0];
		spawn_proc(in, fd[1], cmd, shell);
		shell->to_close = 0;
		if (in)
			close(in);
		in = fd[0];
		close(fd[1]);
		cmd = cmd->next;
	}
	last_cmd(in, cmd, shell);
}
