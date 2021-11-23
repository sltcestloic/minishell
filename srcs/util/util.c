/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:45:53 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/23 14:26:12 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_sep(char c)
{
	return (c == '>' || c == '<' || c == '|' || ft_iswhitespace(c));
}

void	set_term(t_shell *shell)
{
	tcgetattr(0, &shell->new);
	shell->new.c_lflag &= ~ECHOCTL;
	shell->new.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->new);
}

void	unset_term(t_shell *shell)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->old);
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
