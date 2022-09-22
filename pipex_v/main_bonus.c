/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:03:26 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/01 00:03:26 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
//int	ms_executor(t_prgm *vars)
{
	t_prgm vars;

	(void)argc;
	(void)argv;
	/** initialise the program struct and test syncronise with pipex */
	// token 1
	vars.pipe_ct = 1;
	vars.env = env;
	vars.tokens = malloc(sizeof(t_token) * 2);
	vars.tokens[0].in = "<<";
	vars.tokens[0].out = "";
	vars.tokens[0].bin = "";
	vars.tokens[0].t_str = "ls -l";
	vars.tokens[0].built_in = 0;
	vars.tokens[0].cmd = "ls";
	// token2
	vars.tokens[1].in = ">>";
	vars.tokens[1].out = "";
	vars.tokens[1].bin = "";
	vars.tokens[1].t_str = "wc -l";
	vars.tokens[1].built_in = 0;
	vars.tokens[1].cmd = "wc";
	ft_init_pipe(&vars);
	if (ft_valid_args(&vars) == 0)
	 	exit(0);
	ft_generate_p(&vars);
	while (vars.p.child < vars.pipe_ct + 1)
	{
		vars.p.pid[vars.p.child] = fork();
		if (vars.p.pid[vars.p.child] == 0)
		{
			ft_childs_process(&vars);
			execve(vars.tokens[vars.p.child].bin, vars.tokens[vars.p.child].options, vars.env);
		}
		vars.p.child += 1;
	}
	ft_parent_process(&vars);
	return (0);
}
