/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:47:09 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/31 18:47:09 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include "../inc/pipex.h"

void	ft_generate_p(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		if (pipe(vars->p.fd[i]) < 0)
		{
			perror("Error pipe ");
			exit(0);
		}
		i++;
	}
}

void	free_2_pt(char **pt)
{
	int	i;

	i = 0;
	while (pt[i])
	{
		free(pt[i]);
		i++;
	}
	free(pt);
}

void	ft_exit_code(int ex_code, int mode)
{
	if (mode == 0)
		printf("%d", exit_code);
	else
	{
		if (ex_code < 0)
			exit_code = (ex_code * -1) % 256;
		else
			exit_code = ex_code % 256;
	}
}
