/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:33:54 by mochan            #+#    #+#             */
/*   Updated: 2022/11/15 23:25:26 by fakouyat         ###   ########.fr       */
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
	vars->tok[i].opts = NULL;
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
	vars->d_v = NULL;
	vars->tmp = NULL;
	vars->env_head = init_env(vars);
	vars->builts[0] = "cd";
	vars->builts[1] = "echo";
	vars->builts[2] = "env";
	vars->builts[3] = "exit";
	vars->builts[4] = "export";
	vars->builts[5] = "pwd";
	vars->builts[6] = "unset";
}

void	free_env(t_prgm *v)
{
	t_env	*env;

	v->ct1[3] = ft_list_size(v->env_head);
	v->ct1[2] = 0;
	while (v->ct1[2] < v->ct1[3])
	{
		env = v->env_head->next;
		free(v->env_head->key);
		if (v->env_head->value)
			free(v->env_head->value);
		free(v->res[v->ct1[2]]);
		free(v->env_head);
		v->env_head = env;
		v->ct1[2] += 1;
	}
	free(v->res);
	free(v->env_head);
}
