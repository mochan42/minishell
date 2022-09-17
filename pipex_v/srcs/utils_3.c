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

#include "../pipex.h"

void	ft_generate_p(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmd - 1)
	{
		if (pipe(p->fd[i]) < 0)
		{
			perror("Error pipe ");
			exit(0);
		}
		i++;
	}
}

int	ft_valid_nb_args_bonus(int argc)
{
	if (argc < 5)
	{
		ft_printf("Error : fews arguments\n");
		return (0);
	}
	return (1);
}
