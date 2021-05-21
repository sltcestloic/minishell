#include "minishell.h"

int	open_creat(char *file_path)
{
	int fd;

	fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	return (0);
}

int	open_dup_redirect(t_cmd *cmd, int fd_stream)
{
	int fd;

	if (fd_stream == 0)
		fd = open(cmd->value[0], O_RDWR, 0644);
	else if (cmd->type == 4)
		fd = open(cmd->value[0], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->value[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	if (dup2(fd, fd_stream) == -1)
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

int	init_fd(t_shell *shell)
{
	shell->fdsys.fd_in = dup(0);
	if (shell->fdsys.fd_in == -1)
		{
			ft_putstr_fd(strerror(errno), 1);
			return (-1);
		}
	shell->fdsys.fd_out = dup(1);
	if (shell->fdsys.fd_out == -1)
		{
			ft_putstr_fd(strerror(errno), 1);
			return (-1);
		}
	return (0);
}

int	middle_redirect(t_cmd *cmd, int in_out)
{	
	int fd;

	if (in_out)
	{
		if (open_creat(cmd->value[0]))
			return (-1);
		return (0);
	}
	fd = open(cmd->value[0], O_RDWR, 0644);
	if (fd == -1)
		return (-1);
	return (0);
}

int	redirect_it(t_cmd *cmd, int in_out)
{
	t_cmd *save;
	t_cmd *final;

	save = cmd;
	final = 0;
	while (cmd)
	{
		if (cmd->type == in_out + 2)
			final = cmd;
		cmd = cmd->next;
	}
	if (!final)
		return (0);
	cmd = save;
	while (cmd != final)
	{
		if (cmd->type == in_out + 2)
			if (middle_redirect(cmd, in_out))
				return (-1);
		cmd = cmd->next;
	}
	if (open_dup_redirect(save, in_out) == -1)
			return (-1);
	return (0);
}

int	redirect(t_cmd *cmd)
{
	if (redirect_it(cmd, 0))
		return (-1);
	if (redirect_it(cmd, 1))
		return (-1);
	return (0);
}