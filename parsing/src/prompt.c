/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:49:51 by mochan            #+#    #+#             */
/*   Updated: 2022/10/06 01:10:33 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../minishell.h"
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
	int		i;
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
			pid = fork();
			if (pid == 0)
				ms_executor(vars);
			else
				wait(NULL);
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

// int	main(int ac, char **av, char **env)
// {
// 	t_prgm	*ms;

// 	(void)ac;
// 	(void)av;
// 	ms = malloc(sizeof(t_prgm) * 1);
// 	ms->env = env;
// 	init(ms);
// print_dir();
// 	input_loop(ms);
// 	free_stuff(ms);
// 	return (0);
// }
