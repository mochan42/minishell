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
void	ft_childs_process(t_pipe *p)
{
	if (p->child == 0)
		ft_exec_cmd_1(p);
	else if (p->child > 0 && p->child < p->nb_cmd - 1)
	{
		dup2(p->fd[p->child - 1][0], 0);
		dup2(p->fd[p->child][1], 1);
	}
	else if (p->child == p->nb_cmd - 1)
		ft_exec_cmd_last(p);
	ft_close_fds(p);
}
