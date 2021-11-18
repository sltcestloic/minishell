/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:31:28 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/18 18:36:04 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_here_doc(t_redirect *heredoc, int *fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (42)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(heredoc->file_name, line))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

int	parse_here_doc(t_redirect *heredoc, t_shell *shell)
{
	int		pid;
	int		fd[2];

	pipe(fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
		fork_here_doc(heredoc, fd);
	waitpid(pid, &pid, 0);
	if (WIFSIGNALED(pid))
	{
		write(1, "\n", 1);
		last_exit = 1;
		signal(SIGQUIT, signal_reset);
		signal(SIGINT, signal_reset);
		return (-1);
	}
	close(fd[1]);
	heredoc->variation = fd[0];
	return (0);
}

void	here_doc(t_redirect *heredoc)
{
	if (dup2(heredoc->variation, 0) == -1)
	{
		perror("dup2");
		last_exit = 1;
		exit(last_exit);
	}
	if (close(heredoc->variation) == -1)
	{
		perror("close");
		last_exit = 1;
		exit(last_exit);
	}
}

int	do_heredoc(t_cmd *cmd, t_shell *shell)
{
	t_redirect	*i;

	while (cmd)
	{
		i = cmd->in;
		while (i)
		{
			if (cmd->in->variation)
				if (parse_here_doc(i, shell))
					return (-1);
			i = i->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
