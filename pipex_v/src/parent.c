/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 01:15:41 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/18 01:15:41 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parent_process(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct - 1)
	{
		close(vars->p.fd[i][0]);
		close(vars->p.fd[i][1]);
		i++;
	}
	i = 0;
	while (i < vars->pipe_ct)
	{
		wait(&vars->p.status);
		i++;
	}
	vars->p.child -= 1;
	if (vars->tok[vars->p.child].built_in == 0)
		ft_exit_code(WEXITSTATUS(vars->p.status), 1);
	else if (ft_is_env_buil_ins_check(vars) != 1)
		ft_exit_code(0, 1);
	free_vars_p(vars);
}
