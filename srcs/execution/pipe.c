/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owlly <owlly@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:49:19 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/24 15:16:36 by owlly            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	fork_exec(int in, int out, t_cmd *cmd, t_shell *shell)
{
	if (shell->to_close)
		close(shell->to_close);
	if (in && dup_close(in, 0))
		exit(-1);
	if (out != 1 && dup_close(out, 1))
		exit(-1);
	redirect(cmd, NULL, NULL);
	if (cmd->value)
		to_exec(shell, cmd->value);
	g_last_exit = 0;
	exit(g_last_exit);
}

void wait_child(int in, int pid)
{
	int already_sig;

	already_sig = 0;
	if (in)
		close(in);
	waitpid(pid, &pid, 0);
	g_last_exit = WEXITSTATUS(pid);
	already_sig = signal_handle(pid);
	while (waitpid(-1, &pid, 0) != -1)
		if (!already_sig)
			already_sig = signal_handle(pid);
}

int	spawn_proc(int in, int out, t_cmd *cmd, t_shell *shell)
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
	if (pid == -1)
		return (-1);
	if (out == 1)
		wait_child(in, pid);
	return (0);
}

static void	last_cmd(int in, t_cmd *cmd, t_shell *shell)
{
	if (is_built_in(cmd))
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
		if (pipe(fd) == -1 && err_pipe(in))
			return ;
		shell->to_close = fd[0];
		if (spawn_proc(in, fd[1], cmd, shell) && err_proc(in, fd[0], fd[1]))
			return ;
		shell->to_close = 0;
		if (in)
			close(in);
		in = fd[0];
		close(fd[1]);
		cmd = cmd->next;
	}
	last_cmd(in, cmd, shell);
}
