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

#include "../pipex.h"

void	ft_parent_process(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmd - 1)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i++;
	}
	close(p->fd_args[0]);
	close(p->fd_args[1]);
	i = 0;
	while (i < p->nb_cmd)
	{
		wait(&p->status);
		i++;
	}
	unlink("tmp.txt");
}
