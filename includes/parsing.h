/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:16:13 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/16 13:48:29 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_command
{
				char	*name;
				char	**args;
}				t_command;

typedef struct s_split
{
			int	quote1;
			int	quote2;
}				t_split;

void	parse_input(char *input);

/*
** Commands parsing
*/

void	parse_echo(t_command *cmd);


int		count_cmds(const char *str, char c);
char	**ft_splitcmds(const char *str, char c);

#endif