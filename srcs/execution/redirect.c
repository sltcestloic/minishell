#include "minishell.h"

int	parse_here_doc(t_redirect *heredoc, t_shell *shell, int ret)
{
	char	*line;
	char	*save;
	char	*to_free;

	save = NULL;
	while (ret)
	{
		write(1, "> ", 2);
		ret = ft_get_next_line(0, &line);
		if (ret > 0 && ft_strcmp(line, heredoc->file_name))
		{
			to_free = save;
			save = ft_strjoin(save, line, shell->to_free);
			save = ft_strjoin(save, "\n", shell->to_free);
			free(to_free);
			free(line);
		}
		else
		{
			free(line);
			break ;
		}
	}
	heredoc->file_name = save;
	return (0);
}

int	here_doc(t_redirect *heredoc)
{
	int	fd[2];

	if (pipe(fd))
		return (-1);
	write(fd[1], heredoc->file_name, ft_strlen(heredoc->file_name));
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
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
