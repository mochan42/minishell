/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:01:27 by mochan            #+#    #+#             */
/*   Updated: 2022/11/15 23:08:31 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	re_init_tokens(t_prgm *vars)
{
	free_mini(vars);
	vars->pipe_ct = 0;
	vars->tok_error = 0;
	vars->cmd_line = NULL;
}

void	free_inputs(t_prgm *v, int i)
{
	v->ct1[0] = 0;
	while (v->ct1[0] < v->tok[i].nb_input)
	{
		if (v->tok[i].infile != NULL)
		{
			if (v->tok[i].infile[v->ct1[0]])
				free(v->tok[i].infile[v->ct1[0]]);
		}
		v->ct1[0] += 1;
	}
	if (v->tok[i].infile != NULL)
		free(v->tok[i].infile);
	if (v->tok[i].in)
		free(v->tok[i].in);
}

void	free_ouputs(t_prgm *v, int i)
{
	v->ct1[1] = 0;
	while (v->ct1[1] < v->tok[i].nb_output)
	{
		if (v->tok[i].outfile != NULL)
		{
			if (v->tok[i].outfile[v->ct1[1]])
				free(v->tok[i].outfile[v->ct1[1]]);
		}
		v->ct1[1] += 1;
	}
	if (v->tok[i].outfile != NULL)
		free(v->tok[i].outfile);
	if (v->tok[i].out)
		free(v->tok[i].out);
}

void	free_toks(t_prgm *v, int i)
{
	if (v->tok[i].rf_d)
		free(v->tok[i].rf_d);
	if (v->tok[i].cmd)
		free(v->tok[i].cmd);
	if (v->tok[i].bin)
		free(v->tok[i].bin);
	if (v->tok[i].opts)
		free_2_pt(v->tok[i].opts);
}

void	free_mini(t_prgm *v)
{
	int	i;

	if (v->pipe_ct < 1)
		return ;
	i = 0;
	while (i < v->pipe_ct)
	{
		if (v->tok[i].t_str)
		{
			free(v->tok[i].t_str_og);
			v->tok[i].t_str = NULL;
			free(v->tok[i].t_str);
			v->tok[i].t_str_og = NULL;
		}
		i++;
	}
	if (v->tok)
		free(v->tok);
}
