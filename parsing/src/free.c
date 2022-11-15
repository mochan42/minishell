/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:01:27 by mochan            #+#    #+#             */
/*   Updated: 2022/11/15 20:35:57 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		exit (1);
	while (table[i] != NULL)
	{
		free(table[i]);
		i++;
	}
	free(table);
}

void	re_init_tokens(t_prgm *vars)
{
	int	i;

	i = 0;
	// if (vars->pipe_ct > 0)
	// {
	// 	while (i < vars->pipe_ct)
	// 	{
	// 		free(vars->tok[i].t_str);
	// 		free(vars->tok[i].t_str_og);
	// 		vars->tok[i].t_str = NULL;
	// 		vars->tok[i].t_str_og = NULL;
	// 		i++;
	// 	}
	// }
	free_mini(vars);
	vars->pipe_ct = 0;
	vars->tok_error = 0;
	vars->cmd_line = NULL;
}

void	free_stuff(t_prgm *vars)
{
	free(vars->tok);
	free(vars);
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