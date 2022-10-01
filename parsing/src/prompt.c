/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:49:51 by mochan            #+#    #+#             */
/*   Updated: 2022/09/30 18:36:12 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// Function to print Current Directory.
void	print_dir(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s\n", cwd);
}

// Function to take input
int	input_loop(t_prgm *vars)
{
	int	flag;
	int	pid;

	while (1)
	{
		vars->cmd_line = readline("minishell ⚽️$");
		if (!vars->cmd_line)
			return (0);
		flag = 1;
		if (vars->cmd_line)
		{
			add_history(vars->cmd_line);
			parsing(vars);
			pid = fork();
			if (pid == 0)
				ms_executor(vars);
			else
				wait(NULL);
			flag = 0;
		}
		if (flag == 0)
			re_init_tokens(vars);
	}
	return (0);
}
