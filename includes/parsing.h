/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:16:13 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/14 15:16:40 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_command
{
				char	*name;
				char	**args;
}				t_command;

void	parse_input(char *input);

/*
** Commands parsing
*/

void	parse_echo(t_command *cmd);

#endif