#include "minishell.h"

int	open_creat(char *file_path)
{
	int fd;

	fd = open(file_path, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		return (-1);
	}
	return (0);
}

int	open_dup_redirect(char *file_path, int fd_stream)
{
	int fd;

	fd = open(file_path, O_RDWR | O_CREAT, 0644);
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
	if (cmd->next && cmd->next->type == 3)
	{
		while (save->next && save->next->type == 3)
		{
			if (open_creat(save->value[0]) == -1)
				return (-1);
			save = save->next;
		}
		if (open_dup_redirect(save->value[0], 1) == -1)
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
		if (open_dup_redirect(save->value[0], 0) == -1)
			return (-1);
		while (save->next && save->next->next && save->next->next->type == 3)
		{
			if (open_creat(save->next->value[0]) == -1)
				return (-1);
			save = save->next;
		}
		if (open_dup_redirect(save->next->value[0], 1) == -1)
			return (-1);
	}
	else if (redirect_out(cmd) == -1)
		return (-1);
	return (0);
}