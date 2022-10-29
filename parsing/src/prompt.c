/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:49:51 by mochan            #+#    #+#             */
/*   Updated: 2022/10/29 02:08:23 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	high_level_tasks(t_prgm *vars)
{
	int		pid;

	add_history(vars->cmd_line);
	parsing(vars);
	if (vars->tokens[0].built_in == 1)
		ms_executor(vars);
	else
	{
		pid = fork();
		if (pid == 0)
			ms_executor(vars);
		else
			wait(NULL);
	}
}

// Function to take input
int	input_loop(t_prgm *vars)
{
	int		flag;
	
	while (1)
	{
		vars->cmd_line = readline("minishell ⚽️$");
		if (!vars->cmd_line)
			ft_exit(vars);
		flag = 1;
		if (vars->cmd_line[0] && vars->cmd_line[0] != '\n')
		{
			high_level_tasks(vars);
			flag = 0;
		}
		if (flag == 0)
			re_init_tokens(vars);
	}
	return (0);
}
