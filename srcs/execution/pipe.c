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

void	signal_reset(int osef)
{
	(void)osef;
}

void	spawn_proc(int in, int out, t_cmd *cmd, t_shell *shell)
{
	int	pid;

	unset_term(shell);
	signal(SIGQUIT, signal_reset);
	signal(SIGINT, signal_reset);
	pid = fork();
	if (!pid)
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
		last_exit = 0;
		exit(last_exit);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (out == 1)
	{
		waitpid(pid, &pid, 0);
		last_exit = WEXITSTATUS(pid);
		if (WIFSIGNALED(pid))
		{
			if (WTERMSIG(pid) == SIGQUIT)
			{
				printf("Quit: 3\n");
				last_exit = 131;
			}
			else
			{
				last_exit = 130;
				printf("\n");
			}
		}
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
			export(shell->env_var, shell);
		else if (cmd->value[1])
			update_env_value(shell, cmd->value);
	}
	else if (!ft_strcmp(cmd->value[0], "unset"))
		remove_env_elem(cmd->value, shell);
	else if (!ft_strcmp(cmd->value[0], "exit"))
		exit_cmd(shell, cmd->value, 0);
	else if (!ft_strcmp(cmd->value[0], "cd"))
		change_pwd(shell, cmd->value[1]);
	else if (!ft_strcmp(cmd->value[0], "pwd"))
		pwd(shell);
	else
		return (1);
	return (0);
}

static int	is_built_in(t_cmd *cmd)
{
	if (!cmd->value)
		return (0);
	else if (!ft_strcmp(cmd->value[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->value[0], "pwd"))
		return (1);
	else
		return (0);
}

static int	redirect_to_built_in(t_cmd *cmd, t_shell *shell)
{
	int	in;
	int	out;
	int	ret;

	in = dup(0);
	out = dup(1);
	ret = redirect(cmd);
	if (cmd->value)
	{
		if (ret == -1)
		{
			print_error(cmd->value[0], ": Error redirection\n", shell->to_free);
			close(in);
			close(out);
			return (-1);
		}
		ret = do_built_in(cmd, shell);
	}
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	return (ret);
}

void	last_cmd(int in, t_cmd *cmd, t_shell *shell)
{
	if (in)
	{
		spawn_proc(in, 1, cmd, shell);
		close(in);
		while (wait(NULL) != -1)
			;
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
	if (do_heredoc(cmd, shell) == -1)
		return ;
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
	last_cmd(in, cmd, shell);
}
