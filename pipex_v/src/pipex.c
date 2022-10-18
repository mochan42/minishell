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

#include "../../minishell.h"
#include "../inc/pipex.h"

int	ms_executor(t_prgm *vars)
{

	ft_init_pipe(vars);
	if (ft_valid_args(vars) == 0)
	 	exit(0);
	ft_generate_p(vars);
	while (vars->p.child < vars->pipe_ct + 1)
	{
		if (ft_strncmp(vars->tokens[vars->p.child].options[0], "cd", 2) == 0)
			ft_cd(vars);
		else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "export", 6) == 0 && vars->tokens[vars->p.child].options[1])
			ft_export(vars);
		else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "exit", 4) == 0)
			ft_exit(0);
		else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "unset", 5) == 0)
			ft_unset(vars);
		else
		{
			vars->p.pid[vars->p.child] = fork();
			if (vars->p.pid[vars->p.child] == 0)
			{
				ft_childs_process(vars);
				if (vars->tokens[vars->p.child].built_in == 1)
					execbuilt_in(vars);
				else if (ft_is_error(vars) == 1 && is_our_env_path(vars) == 1)
					execve(vars->tokens[vars->p.child].bin, vars->tokens[vars->p.child].options, vars->env);
				else
				{
					printf("Environment PATH doesn't exist\n");
					exit(0);
				}
			}
		}
		vars->p.child += 1;
	}
	ft_parent_process(vars);
	return (0);
}
