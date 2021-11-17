/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:47:00 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/17 08:47:01 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_non_removable(t_parser *parser, char c)
{
	if (c != '\'' && c != '"')
		return (1);
	else if (c == '\'' && parser->d_quote)
		return (1);
	else if (c == '"' && parser->s_quote)
		return (1);
	else
		return (0);
}
