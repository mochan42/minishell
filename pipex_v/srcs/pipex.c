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

#include "../pipex.h"

int	ms_executor(t_prgm vars)
{
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
