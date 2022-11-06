/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:49:51 by mochan            #+#    #+#             */
/*   Updated: 2022/11/06 21:08:23 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	high_level_tasks(t_prgm *vars)
{
	int		pid;
	
	add_history(vars->cmd_line);
	// if (are_quotes_closed(vars->cmd_line) == 1)
	// {
	// 	printf("Quotes are not closed.\n");
	// 	return ;
	// }
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
		if (are_quotes_closed_V2(vars->cmd_line) == 1)
		{
			printf("Quotes are not closed.\n");
			flag = 0;
		}
		else
		{
			flag = 1;
			if (vars->cmd_line[0] && vars->cmd_line[0] != '\n')
			{
				high_level_tasks(vars);
				flag = 0;
			}
		}
		if (flag == 0)
			re_init_tokens(vars);
	}
	return (0);
}
