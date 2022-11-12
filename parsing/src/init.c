/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:33:54 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 18:15:57 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	init_each_token(t_prgm *vars, int i)
{
	vars->tok[i].in = NULL;
	vars->tok[i].out = NULL;
	vars->tok[i].infile = NULL;
	vars->tok[i].outfile = NULL;
	vars->tok[i].bin = NULL;
	vars->tok[i].built_in = 0;
	vars->tok[i].options = NULL;
	vars->tok[i].cmd = NULL;
	vars->p.error[i][0] = '\0';
}

void	init_all_tokens(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct)
	{
		init_each_token(vars, i);
		i++;
	}
}

void	init(t_prgm *vars)
{
	vars->pipe_ct = 0;
	vars->p.child = 0;
	vars->env_head = NULL;
	vars->env_head = init_env(vars);
	vars->builts[0] = "cd";
	vars->builts[1] = "echo";
	vars->builts[2] = "env";
	vars->builts[3] = "exit";
	vars->builts[4] = "export";
	vars->builts[5] = "pwd";
	vars->builts[6] = "unset";
}
