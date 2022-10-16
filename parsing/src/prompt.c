/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:49:51 by mochan            #+#    #+#             */
/*   Updated: 2022/10/16 21:37:53 by mochan           ###   ########.fr       */
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
	int		flag;
	int		pid;
	char	repo[MAX_LEN_DIR];
	int		tmp_fd;
	char	*tmp;

	while (1)
	{
		if (vars->curr_dir[0] == '\0')
			ft_strlcpy(vars->curr_dir, getcwd(repo, MAX_LEN_DIR), MAX_LEN_DIR);
		vars->cmd_line = readline("minishell ⚽️$");
		if (!vars->cmd_line)
			return (0);
		flag = 1;
		if (vars->cmd_line)
		{
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
			tmp_fd = open("cwd.txt", O_RDONLY);
			ft_bzero(vars->curr_dir, MAX_LEN_DIR);
			tmp = get_next_line(tmp_fd);
			if(tmp)
			{
				ft_strlcpy(vars->curr_dir, tmp, MAX_LEN_DIR);
				free(tmp);
			}
			close(tmp_fd);
			unlink("cwd.txt");
			flag = 0;
		}
		if (flag == 0)
			re_init_tokens(vars);
	}
	return (0);
}
