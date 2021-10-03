#include "minishell.h"

void	spawn_proc(int in, int out, t_cmd *cmd, t_shell *shell)
{
	int pid;

	pid = fork();
	if (!pid)
	{
		if (in)
		{
			dup2(in, 0);
			close(in);
		}
		if (out > 1)
		{
			dup2(out, 1);
			close(out);
		}
		redirect(cmd);
		to_exec(shell, cmd->value);
		exit(-1);
	}
}

void	cmd_parse(t_cmd *cmd, t_shell *shell)
{
	int in = 0;
	int fd[2];

	while (cmd->next)
	{
		pipe(fd);
		spawn_proc(in, fd[1], cmd, shell);
		in = fd[0];
		cmd = cmd->next;
	}
	spawn_proc(in, 1, cmd, shell);
}
