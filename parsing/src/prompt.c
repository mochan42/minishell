/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:49:51 by mochan            #+#    #+#             */
/*   Updated: 2022/11/11 19:54:17 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	high_level_tasks(t_prgm *vars)
{
	vars->tok_error = 0;
	add_history(vars->cmd_line);
	parsing(vars);
	if (vars->tok_error >= 1)
	{	
		exit_code = 1;
		return ;
	}
	ms_executor(vars);
}

// Function to take input
int	input_loop(t_prgm *vars)
{
	vars->cmd_line = ft_strdup(readline("minishell ⚽️$"));
	printf("%s", vars->cmd_line);
	if (!vars->cmd_line)
		ft_exit_shell(vars);
	else if (*vars->cmd_line == '\0')
		return (0);
	else
	{
		if (are_quotes_closed_v3(vars->cmd_line) == 1)
			printf("Quotes are not closed.\n");
		else
			high_level_tasks(vars);
		re_init_tokens(vars);
	}
	free(vars->cmd_line);
	vars->cmd_line = NULL;
	return (0);
}
