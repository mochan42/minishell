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

void	close_in_outfiles(t_prgm *vars, int i)
{
	int	j;

	j = 0;
	if (vars->tok[i].infile != NULL)
	{
		while (vars->tok[i].infile[j])
		{
			close(vars->tok[i].fd_args[j][0]);
			j++;
		}
	}
	j = 0;
	if (vars->tok[i].outfile != NULL)
	{
		while (vars->tok[i].outfile[j])
		{
			close(vars->tok[i].fd_args[j][1]);
			j++;
		}
	}
}

void	ft_parent_process(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct - 1)
	{
		close(vars->p.fd[i][0]);
		close(vars->p.fd[i][1]);
		close_in_outfiles(vars, i);
		i++;
	}
	i = 0;
	while (i < vars->pipe_ct)
	{
		wait(&vars->p.status);
		i++;
	}
	vars->p.child -= 1;
	if (vars->tok[vars->p.child].built_in == 0 || is_our_env_path(vars) != 1)
		ft_exit_code(WEXITSTATUS(vars->p.status), 1);
	free_vars_p(vars);
}
