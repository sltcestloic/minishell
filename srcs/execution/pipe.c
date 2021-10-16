#include "minishell.h"

int	has_heredoc(t_cmd *cmd)
{
	if (!cmd->in)
		return (0);
	while (cmd->in->next)
	{
		if (cmd->in->variation)
			return (1);
		cmd->in = cmd->in->next;
	}
	if (cmd->in->variation)
		return (1);
	return (0);
}

void	spawn_proc(int in, int out, t_cmd *cmd, t_shell *shell)
{
	int pid;

	pid = fork();
	if (!pid)
	{
		if (in && !has_heredoc(cmd))
		{
			dup2(in, 0);
			close(in);
		}	
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		redirect(cmd);							//error
		to_exec(shell, cmd->value);
	}
	if (out == 1 || has_heredoc(cmd))
	{
		waitpid(pid, &pid, 0);
		shell->last_exit_return = WEXITSTATUS(pid);
	}
}

void	cmd_parse(t_cmd *cmd, t_shell *shell)
{
	int in;
	int fd[2];

	in = 0;
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
	}
	if (in)
	{
		spawn_proc(in, 1, cmd, shell);
		close(in);
		while (wait(NULL) != -1)
			;
	}
	else
		spawn_proc(in, 1, cmd, shell);
}
