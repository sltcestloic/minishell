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

int	redirect_out(t_cmd *cmd)
{
	t_cmd *save;

	save = cmd->next;
	if (cmd->next && (cmd->next->type == 3 || cmd->next->type == 4))
	{
		while (save->next && (save->next->type == 3 || cmd->next->type == 4))
		{
			if (open_creat(save->value[0]) == -1)
				return (-1);
			save = save->next;
		}
		if (open_dup_redirect(save, 1) == -1)
			return (-1);
	}
	return (0);
}

int	redirect(t_cmd *cmd)
{
	t_cmd *save;

	save = cmd->next;
	if (cmd->next && cmd->next->type == 2)
	{
		if (open_dup_redirect(save, 0) == -1)
			return (-1);
		while (save->next && save->next->next &&
		(save->next->next->type == 3 || save->next->next->type == 4))
		{
			if (open_creat(save->next->value[0]) == -1)
				return (-1);
			save = save->next;
		}
		if (save->next)
			if (open_dup_redirect(save->next, 1) == -1)
				return (-1);
	}
	else if (redirect_out(cmd) == -1)
		return (-1);
	return (0);
}