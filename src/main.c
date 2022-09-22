/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:49:51 by mochan            #+#    #+#             */
/*   Updated: 2022/09/22 19:41:07 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	int	i;

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
			ms_executer(vars);
			flag = 0;
		}
		i = 0;
		if (flag == 0)
		{
			if (vars->pipe_ct > 0)
			{
				while (i < vars->pipe_ct + 1)
				{
					free(vars->tokens[i].t_str);
					i++;
				}
			}
			vars->pipe_ct = 0;
		}
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_prgm	*ms;

	(void)ac;
	(void)av;
	ms = malloc(sizeof(t_prgm) * 1);
	ms->env = env;
	init(ms);
	// print_dir();
	input_loop(ms);
	free_stuff(ms);
	return (0);
}
