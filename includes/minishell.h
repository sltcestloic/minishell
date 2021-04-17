/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:15:04 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/17 13:09:46 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "parsing.h"
# include "exec.h"

void	display_prompt(t_shell *shell);

/*
** Utils
*/

int		ft_splitlen(char **split);

#endif