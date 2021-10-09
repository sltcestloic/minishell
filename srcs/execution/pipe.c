#include "minishell.h"

void	update_last_exit_value(t_shell *shell, int i)
{
	int status;

	status = 0;
	while (i)
	{
		waitpid(-1, &status, 0);
		shell->last_exit_return = WEXITSTATUS(status);
		i--;
	}
}

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
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		// redirect(cmd);
		to_exec(shell, cmd->value);
		exit(0);
	}
}

void	cmd_parse(t_cmd *cmd, t_shell *shell)
{
	int in;
	int number_of_child;
	int fd[2];

	in = 0;
	number_of_child = 1;
	while (cmd->next)
	{
		pipe(fd);
		spawn_proc(in, fd[1], cmd, shell);
		in = fd[0];
		cmd = cmd->next;
		number_of_child++;
	}
	spawn_proc(in, 1, cmd, shell);
	update_last_exit_value(shell, number_of_child);
}
