/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:33:54 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 01:23:11 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	init_each_token(t_prgm *vars, int i)
{
	vars->tokens[i].in = NULL;
	vars->tokens[i].out = NULL;
	vars->tokens[i].infile = NULL;
	vars->tokens[i].outfile = NULL;
	vars->tokens[i].bin = NULL;
	vars->tokens[i].built_in = 0;
	vars->tokens[i].options = NULL;
	vars->tokens[i].cmd = NULL;
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
