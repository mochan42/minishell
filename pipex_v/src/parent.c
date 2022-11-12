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
	int	j;

	i = 0;
	while (i < vars->pipe_ct - 1)
	{
		j = 0;
		close(vars->p.fd[i][0]);
		close(vars->p.fd[i][1]);
		if (vars->tokens[i].infile != NULL)
		{
			while (vars->tokens[i].infile[j])
			{
				close(vars->tokens[i].fd_args[j][0]);
				j++;
			}
		}
		if (vars->tokens[i].outfile != NULL)
		{
			while (vars->tokens[i].outfile[j])
			{
				close(vars->tokens[i].fd_args[j][1]);
				j++;
			}
		}
		i++;
	}
	i = 0;
	while (i < vars->pipe_ct)
	{
		wait(&vars->p.status);
		i++;
	}
	vars->p.child -= 1;
	if (vars->tokens[vars->p.child].built_in == 0 || is_our_env_path(vars) != 1)
		ft_exit_code(WEXITSTATUS(vars->p.status), 1);
	free_vars_p(vars);
}
