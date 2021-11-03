#include "minishell.h"

void	print_error(char *cmd, char *msg, t_free *to_free)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(cmd, 2);
	write(2, &msg, ft_strlen(msg));
	ft_exit(to_free);
}

int	do_heredoc(t_cmd *cmd, t_shell *shell)
{
	t_redirect *i;
	while (cmd)
	{
		i = cmd->in;
		while (i)
		{
			if (cmd->in->variation)
				parse_here_doc(i, shell);
			i = cmd->in->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

void	spawn_proc(int in, int out, t_cmd *cmd, t_shell *shell)
{
	int pid;

	pid = fork();
	if (!pid)
	{
		if (shell->to_close)
			close(shell->to_close);
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
		if (redirect(cmd) == -1)
			print_error(cmd->value[0], ": Error during redirection\n", shell->to_free);
		to_exec(shell, cmd->value);
	}
	if (out == 1)
	{
		waitpid(pid, &pid, 0);
		shell->last_exit_return = WEXITSTATUS(pid);
	}
}

static int	do_built_in(t_cmd *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->value[0], "echo"))
		echo(cmd->value);
	else if (!ft_strcmp(cmd->value[0], "env"))
		env(shell->env_var);
	else if (!ft_strcmp(cmd->value[0], "export"))
	{
		if (!cmd->value[1])
			export(shell->env_var);
		else if(cmd->value[1])
			update_env_value(shell, cmd->value);
	}
	else if (!ft_strcmp(cmd->value[0], "unset"))
		remove_env_elem(cmd->value, shell);
	else if (!ft_strcmp(cmd->value[0], "exit"))
		exit_cmd(shell, cmd->value);
	else if (!ft_strcmp(cmd->value[0], "cd"))
		change_pwd(shell, cmd->value[1]);
	else if (!ft_strcmp(cmd->value[0], "pwd"))
		pwd(shell);
	else
		return (1);
	return (0);
}

static int	redirect_to_built_in(t_cmd *cmd, t_shell *shell)
{
	int in;
	int out;
	int ret;

	in = dup(0);
	out = dup(1);
	ret = redirect(cmd);
	if (ret == -1)
	{
		print_error(cmd->value[0], ": Error during redirection\n", shell->to_free);
		return(-1);
	}
	ret = do_built_in(cmd, shell);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	return (ret);
}

void	cmd_parse(t_cmd *cmd, t_shell *shell)
{
	int in;
	int fd[2];

	in = 0;
	do_heredoc(cmd, shell);
	while (cmd->next)
	{
		if (pipe(fd))
			print_error(cmd->value[0], ": Error during pipe\n", shell->to_free);
		shell->to_close = fd[0];
		spawn_proc(in, fd[1], cmd, shell);
		shell->to_close = 0;
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
	else if (redirect_to_built_in(cmd, shell))
		spawn_proc(in, 1, cmd, shell);
}
