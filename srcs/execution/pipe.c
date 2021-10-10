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
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		// redirect(cmd);
		to_exec(shell, cmd->value);
	}
	if (out == 1)
		waitpid(pid, &pid, 0);
	shell->last_exit_return = WEXITSTATUS(pid);
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
		if (pipe(fd))
			return ;									//error
		spawn_proc(in, fd[1], cmd, shell);
		if (in)
			close(in);
		in = fd[0];
		close(fd[1]);
		cmd = cmd->next;
		number_of_child++;
	}
	if (number_of_child > 1)
	{
		close(fd[1]);
		spawn_proc(in, 1, cmd, shell);
		close(in);
	}
	else
		spawn_proc(in, 1, cmd, shell);
	while (--number_of_child)
		wait(&in);
}
