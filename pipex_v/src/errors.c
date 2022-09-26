/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:08:40 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/29 15:08:40 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include "../inc/pipex.h"

int	ft_is_error(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct)
	{
		if (vars->p.error[i][0] != '\0')
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_err_message(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct)
	{
		if (vars->p.error[i][0] != '\0')
			printf("%s\n", vars->p.error[i]);
		i++;
	}
}
