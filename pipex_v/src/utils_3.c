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
	while (i < vars->pipe_ct - 1)
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
		printf("%d", g_exit_code);
	else
	{
		if (ex_code < 0)
			g_exit_code = (ex_code * -1) % 256;
		else
			g_exit_code = ex_code % 256;
	}
}

int	ft_assert_numeric(t_prgm *vars, int indice)
{
	int	j;

	j = 0;
	while (vars->tok[vars->p.child].options[indice][j])
	{
		if (is_numeric(
				vars->tok[vars->p.child].options[indice][j]) == 1)
		{
			printf("numeric argument required : %s\n",
				vars->tok[vars->p.child].options[indice]);
			ft_exit_code(255, 1);
			return (1);
		}
		j++;
	}
	return (0);
}

int	is_numeric(char c)
{
	if (!(c >= '0' && c <= '9') && c != '-')
		return (1);
	return (0);
}
