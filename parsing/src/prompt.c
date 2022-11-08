/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:49:51 by mochan            #+#    #+#             */
/*   Updated: 2022/11/08 16:59:35 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	high_level_tasks(t_prgm *vars)
{
	add_history(vars->cmd_line);
	parsing(vars);
	ms_executor(vars);
}

// Function to take input
int	input_loop(t_prgm *vars)
{
	int		flag;
	
	vars->cmd_line = readline("minishell ⚽️$");
	flag = 1;
	if (!vars->cmd_line)
		ft_exit(vars);
	else if (are_quotes_closed_V2(vars->cmd_line) == 1)
	{
		printf("Quotes are not closed.\n");
		flag = 0;
	}
	else
	{
		if (vars->cmd_line[0] && vars->cmd_line[0] != '\n')
		{
			high_level_tasks(vars);
			flag = 0;
		}
	}
	if (flag == 0)
		re_init_tokens(vars);
	return (0);
}
