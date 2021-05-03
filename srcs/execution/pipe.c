#include "minishell.h"
int	pipe_it(t_cmd *cmd, t_shell *shell)
{
	int fd[2];
	int pid;

	pipe(fd);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		wait(NULL);
		if (dup2(fd[0], 0) == -1)
			return (0);
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

	ptr = cmd;
	while (ptr)
	{
		while (ptr && ptr->type != 5)
			ptr = ptr->next;
		if (ptr->type == 5)
		{
			if (pipe_it(cmd, shell) == -1)
				ft_exit(shell->to_free);
			cmd = ptr->next;
			ptr = ptr->next;
		}
		else
			ptr = 0;
	}
	if (pipe_it(cmd, shell) == -1)
		ft_exit(shell->to_free);
}