#include "minishell.h"

int passive_here_doc(char *stop)
{
	char *line;
	int ret;

	ret = 1;
	while (ret)
	{
		ret = ft_get_next_line(0, &line);
		if (ret == -1)
		{
			free(line);
			return (-1);
		}
		if (ft_strcmp(line, stop))
			free(line);
		else
		{
			free(line);
			break;
		}
	}
	return (0);
}

int	here_doc(char *stop)
{
	char *line;
	int fd[2];
	int ret;

	if (pipe(fd))
		return (-1);
	ret = 1;
	while (ret)
	{
		ret = ft_get_next_line(0, &line);
		if (ret == -1)
		{
			free(line);
			return (-1);
		}
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
		return (here_doc(redirect->file_name));
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
		return (passive_here_doc(redirect->file_name));
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