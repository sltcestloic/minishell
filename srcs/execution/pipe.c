#include "minishell.h"

int	fd_restore(t_shell *shell)
{
	if (dup2(shell->fdsys.fd_in, 0) == -1)
		{
			ft_putstr_fd(strerror(errno), 1);
			return (-1);
		}
	if (dup2(shell->fdsys.fd_out, 1) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	return (0);
}

int	pipe_it(t_cmd *cmd, t_shell *shell)
{
	int fd[2];
	int pid;

	if(pipe(fd) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		wait(NULL);
		if (dup2(fd[0], 0) == -1)
			return (-1);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
			exit(-1);
		redirect(cmd);
		to_exec(shell, cmd->value);
		exit(0);
	}
	return (0);
}

void	cmd_parse(t_cmd *cmd, t_shell *shell)
{
	t_cmd *ptr;

	print_cmd(cmd);
	ptr = cmd;
	while (ptr)
	{
		while (ptr && ptr->type != 5)
			ptr = ptr->next;
		if (ptr)
		{
			// write(1, "PIPING\n", 7);
			if (pipe_it(cmd, shell) == -1)
				ft_exit(shell->to_free);
			cmd = ptr->next;
			ptr = ptr->next;
		}
	}
	redirect(cmd);
	to_exec(shell, cmd->value);
	if (fd_restore(shell))
		ft_exit(shell->to_free);
}
