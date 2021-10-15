#include "minishell.h"

int	here_doc(char *stop, int is_active)
{
	char *line;
	int fd[2];

	if (is_active)
	{
		pipe(fd);
		while ((line = readline(NULL)))
		{
			if (ft_strcmp(line, stop))
			{
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
				free(line);
			}
			else
				break;
		}
		free(line);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	else
	{
		while ((line = readline(NULL)))
		{
			if (ft_strcmp(line, stop))
				free(line);
			else
			{
				free(line);
				break;
			}
		}
	}
	return (0);
}

int	redirect_out(t_redirect *redirect)
{
	int fd;

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
	int fd;

	if (redirect->variation)
		return (here_doc(redirect->file_name, 1));
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
	int fd;

	if (redirect->variation)
		return (here_doc(redirect->file_name, 0));
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
	int fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	return (0);
}

int redirect(t_cmd *cmd)
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