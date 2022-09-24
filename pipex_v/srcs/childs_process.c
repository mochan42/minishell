/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_last_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:27:18 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/18 02:27:18 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* redirecting into fd according to the commands */
void	ft_childs_process(t_prgm *vars)
{
	if (vars->p.child == 0)
		ft_exec_cmd_1(vars);
	else if (vars->p.child > 0 && vars->p.child < vars->pipe_ct)
	{
		dup2(vars->p.fd[vars->p.child - 1][0], 0);
		dup2(vars->p.fd[vars->p.child][1], 1);
	}
	else if (vars->p.child == vars->pipe_ct)
		ft_exec_cmd_last(vars);
	ft_close_fds(vars);
}
