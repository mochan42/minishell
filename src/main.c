/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:49:51 by mochan            #+#    #+#             */
/*   Updated: 2022/09/19 19:13:23 by mochan           ###   ########.fr       */
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
int	input_loop(char *str, t_prgm *vars)
{
	char	*buf;
	int		pid_loop;
	int		flag;

	while (1)
	{
		buf = readline("minishell$");
		if (!buf)
			return (0);
		add_history(buf);
		strcpy(str, buf);
		vars->cmd_line = str;
		//parsing : into struct
		if (buf)
		{
			flag = 1;
			parsing(vars);
		}
		if (flag == 1)
		{
			pid_loop = fork();
			if (pid_loop == 0)
				ms_executer(vars);
			else
				wait(NULL);
			free(buf);
			flag = 0;
			//exit function;
		}
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	input_string[MAXCOM];
	t_prgm	*ms;

	(void)ac;
	(void)av;
	ms = malloc(sizeof(t_prgm) * 1);
	ms->env = env;
	init(ms);
	// print_dir();
	input_loop(input_string, ms);
	free_stuff(ms);
	return (0);
}
