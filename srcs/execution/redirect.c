/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:18:05 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/20 16:25:40 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_out(t_redirect *redirect)
{
	int	fd;

	if (redirect->type == APPEND || redirect->type == HEREDOC)
		fd = open(redirect->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redirect->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || dup2(fd, 1) == -1 || close(fd) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirect->file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		g_last_exit = 1;
		exit(g_last_exit);
	}
}

void	redirect_in(t_redirect *redirect)
{
	int	fd;

	if (redirect->type == APPEND || redirect->type == HEREDOC)
	{
		here_doc(redirect);
		return ;
	}
	fd = open(redirect->file_name, O_RDWR, 0644);
	if (fd == -1 || dup2(fd, 0) == -1 || close(fd) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirect->file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		g_last_exit = 1;
		exit(g_last_exit);
	}
}

void	try_open(t_redirect *redirect)
{	
	int	fd;

	if (redirect->type == APPEND || redirect->type == HEREDOC)
		return ;
	fd = open(redirect->file_name, O_RDWR, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirect->file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		g_last_exit = 1;
		exit(g_last_exit);
	}
}

int	creat_trunc_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		g_last_exit = 1;
		exit(g_last_exit);
	}
	return (0);
}

void	redirect(t_cmd *cmd)
{
	while (cmd->redirect && cmd->redirect->next)
	{
		if (cmd->redirect->type == REDIRECT_IN)
		{
			try_open(cmd->redirect);
		}
		else if (cmd->redirect->type == REDIRECT_OUT)
			creat_trunc_file(cmd->redirect->file_name);
		cmd->redirect = cmd->redirect->next;

	}
	if (cmd->redirect)
	{
		if (cmd->redirect->type == REDIRECT_IN)
			redirect_in(cmd->redirect);
		else if (cmd->redirect->type == REDIRECT_OUT)
			redirect_out(cmd->redirect);
	}
}
