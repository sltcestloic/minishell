#include "minishell.h"

int	here_doc(char *stop, int is_active)
{
	char *line;
	int fd;

	if (is_active)
		fd = dup(0);
	line = NULL;
	while (ft_strcmp(line, stop))
	{
		if (is_active && line)
			write(fd, line, ft_strlen(line));
		free(line);
		line = readline(NULL);
	}
	if (is_active)
	{
		dup2(fd, 0);
		close(fd);
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
	if (dup2(fd, 1) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	if (close(fd) == -1)
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
	if (dup2(fd, 0) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	if (close(fd) == -1)
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
	if (redirect_in(cmd->in))
		return (-1);
	while (cmd->out && cmd->out->next)
	{
		creat_trunc_file(cmd->out->file_name);
		cmd->out = cmd->out->next;
	}
	if (redirect_out(cmd->out))
		return (-1);
	return (0);
}