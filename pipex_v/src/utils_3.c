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
	while (i < vars->pipe_ct)
	{
		if (pipe(vars->p.fd[i]) < 0)
		{
			perror("Error pipe ");
			exit(0);
		}
		i++;
	}
}

// int	ft_valid_nb_args_bonus(int argc)
// {
// 	if (argc < 5)
// 	{
// 		ft_printf("Error : fews arguments\n");
// 		return (0);
// 	}
// 	return (1);
// }
