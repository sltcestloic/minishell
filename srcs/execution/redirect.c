#include "minishell.h"

int	parse_here_doc(t_redirect *heredoc, t_shell *shell)
{
	char	*line;
	int		pid;
	int		fd[2];

	pipe(fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
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

int	here_doc(t_redirect *heredoc)
{
	if (dup2(heredoc->variation, 0) == -1)
		perror("dup2");
	if (close(heredoc->variation) == -1)
		perror("close");
	return (0);
}

int	redirect_out(t_redirect *redirect)
{
	int	fd;

	if (redirect->variation)
		fd = open(redirect->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redirect->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || dup2(fd, 1) == -1 || close(fd) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	return (0);
}

int	redirect_in(t_redirect *redirect)
{
	int	fd;

	if (redirect->variation)
		return (here_doc(redirect));
	fd = open(redirect->file_name, O_RDWR, 0644);
	if (fd == -1 || dup2(fd, 0) == -1 || close(fd) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	return (0);
}

int	try_open(t_redirect *redirect)
{	
	int	fd;

	if (redirect->variation)
		return (0);
	fd = open(redirect->file_name, O_RDWR, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	return (0);
}

int	creat_trunc_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	return (0);
}

int	redirect(t_cmd *cmd)
{
	while (cmd->in && cmd->in->next)
	{
		if (try_open(cmd->in))
			return (-1);
		cmd->in = cmd->in->next;
	}
	if (cmd->in)
		if (redirect_in(cmd->in))
			return (-1);
	while (cmd->out && cmd->out->next)
	{
		if (creat_trunc_file(cmd->out->file_name))
			return (-1);
		cmd->out = cmd->out->next;
	}
	if (cmd->out)
		if (redirect_out(cmd->out))
			return (-1);
	return (0);
}
