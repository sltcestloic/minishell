/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:45:51 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/20 16:19:32 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*init_parser(t_shell *shell)
{
	t_parser	*ret;

	ret = (t_parser *)ft_malloc(sizeof(t_parser), &shell->to_free);
	if (!ret)
		ft_malloc_error(shell->to_free);
	ret->d_quote = 0;
	ret->s_quote = 0;
	return ((t_parser *)ret);
}

t_parser	init_parser_nml(void)
{
	t_parser	ret;

	ret.d_quote = 0;
	ret.s_quote = 0;
	return (ret);
}

t_cmd	*init_cmd(t_shell *shell)
{
	t_cmd	*ret;

	ret = (t_cmd *)ft_malloc(sizeof(t_cmd), &shell->to_free);
	if (!ret)
		ft_malloc_error(shell->to_free);
	ret->next = NULL;
	ret->redirect = NULL;
	ret->value = NULL;
	ret->quotes = 0;
	ret->shell = shell;
	return (ret);
}

t_index	init_index(void)
{
	t_index	ret;

	ret.i = 0;
	ret.j = 0;
	ret.k = 0;
	return (ret);
}
