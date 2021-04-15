/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:15:04 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/15 14:27:34 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "parsing.h"
# include "exec.h"

typedef struct s_shell
{
				t_free	*to_free;
}				t_shell;

void	display_prompt(void);

/*
** Utils
*/

int		ft_splitlen(char **split);

#endif