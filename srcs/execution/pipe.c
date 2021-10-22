#include "minishell.h"

void	print_error(char *cmd, char *msg)
{
	write(2, "Minishell: ", 11);
	ft_putstr_fd(cmd, 2);
	write(2, &msg, 28);
	exit(-1);
}

int	do_heredoc(t_cmd *cmd)
{
	t_redirect *i;
	while (cmd)
	{
		i = cmd->in;
		while (i)
		{
			if (cmd->in->variation)
				parse_here_doc(i);
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
			print_error(cmd->value[0], " : Error during redirection\n");
		to_exec(shell, cmd->value);
	}
	if (out == 1)
	{
		waitpid(pid, &pid, 0);
		shell->last_exit_return = WEXITSTATUS(pid);
	}
}

static int	do_built_in(char **func, t_shell *shell)
{
	if (!ft_strcmp(func[0], "echo"))
		echo(func);
	else if (!ft_strcmp(func[0], "env"))
		env(shell->env_var);
	else if (!ft_strcmp(func[0], "export"))
	{
		if (!func[1])
			export(shell->env_var);
		else if(func[1])
			new_env_elem(func[1], shell);
	}
	else if (!ft_strcmp(func[0], "unset"))
		remove_env_elem(func[1], shell);
	else if (!ft_strcmp(func[0], "exit"))
		exit_cmd(shell, func);
	else if (!ft_strcmp(func[0], "cd"))
		change_pwd(shell, func[1]);
	else if (!ft_strcmp(func[0], "pwd"))
		pwd(shell);
	else
		return (1);
	shell->last_exit_return = 0;
	return (0);
}

void	cmd_parse(t_cmd *cmd, t_shell *shell)
{
	int in;
	int fd[2];

	in = 0;
	do_heredoc(cmd);
	while (cmd->next)
	{
		if (pipe(fd))
			print_error(cmd->value[0], " : Error during pipe\n");								//error
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
	else if (do_built_in(cmd->value, shell))
		spawn_proc(in, 1, cmd, shell);
}
