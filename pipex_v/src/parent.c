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
	while (i < vars->pipe_ct)
	{
		wait(&vars->p.status);
		i++;
	}
	unlink("tmp.txt");
}
