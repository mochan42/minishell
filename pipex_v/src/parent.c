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
//#include "../inc/pipex.h"

void	ft_parent_process(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct)
	{
		close(vars->p.fd[i][0]);
		close(vars->p.fd[i][1]);
		i++;
	}
	//close(vars->fd_args[0]);
	//close(vars->fd_args[1]);
	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		wait(&vars->p.status);
		i++;
	}
	if (vars->tokens[vars->p.child - 1].built_in == 0)
		ft_exit_code(WEXITSTATUS(vars->p.status), 1);
	free_vars_p(vars);
}
