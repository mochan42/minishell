/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:41:28 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 19:18:26 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	subs_outfile(t_prgm *v, int *start, int id)
{
	int	len_outfile;
	int	j;

	len_outfile = 0;
	j = *start;
	while (v->tok[v->i].t_str[j] != '\0' \
		&& (v->tok[v->i].t_str[j] != ' ' && v->tok[v->i].t_str[j] != '\t'))
	{
		if ((v->tok[v->i].t_str[j] == '<' || v->tok[v->i].t_str[j] == '>')
			&& (is_btw_q(v->tok[v->i].t_str, '\'', j) == NULL \
			&& is_btw_q(v->tok[v->i].t_str, '"', j) == NULL))
		{
			v->tok_error = 1;
			return ;
		}
		len_outfile++;
		j++;
	}
	if (v->tok[v->i].outfile == NULL)
		return ;
	v->tok[v->i].outfile[id] = trim_quotes \
		(ft_substr(v->tok[v->i].t_str, *start, len_outfile++));
	if (*v->tok[v->i].outfile[id] == '\0' && v->tok[v->i].out[id] != OUT_STD)
		v->tok_error = 1;
	*start += len_outfile - 1;
}

void	extract_outfiles_init(t_prgm *vars)
{
	vars->j = 0;
	vars->index = 0;
	vars->k = 0;
	vars->tok[vars->i].nb_output = count_output(vars);
}

void	extract_outfiles(t_prgm *vars)
{
	extract_outfiles_init(vars);
	if (vars->tok[vars->i].nb_output > 0)
	{
		vars->tok[vars->i].out = malloc(sizeof(int) * \
			(vars->tok[vars->i].nb_output + 1));
		vars->tok[vars->i].outfile = malloc(sizeof(char *) * \
			(vars->tok[vars->i].nb_output + 1));
		vars->tok[vars->i].outfile[vars->tok[vars->i].nb_output] = NULL;
	}
	while (vars->tok[vars->i].t_str[vars->j] != '\0' && vars->tok_error != 1)
	{
		if (vars->j > 0)
		{
			if (is_append_and_not_inside_quotes(vars, vars->j))
				extract_outfile_append_and_fill_in_cmd_string(vars);
			else if (is_output_redirect_and_not_inside_quotes(vars, \
				vars->j - 1))
				extract_outfile_output_redirect_and_fill_in_cmd_string(vars);
			else
				fill_in_cmd_string_no_outfile(vars);
		}
		else
			fill_in_cmd_string_no_outfile(vars);
	}
	vars->tok[vars->i].cmd[vars->k] = '\0';
}

void	find_outfile(t_prgm *vars)
{
	vars->i = 0;
	while (vars->i < vars->pipe_ct)
	{
		free(vars->tok[vars->i].t_str);
		vars->tok[vars->i].t_str = ft_strdup(vars->tok[vars->i].cmd);
		free(vars->tok[vars->i].cmd);
		vars->tok[vars->i].cmd = malloc(sizeof(char) * \
			(ft_strlen(vars->tok[vars->i].t_str) + 1));
		extract_outfiles(vars);
		if (vars->tok[vars->i].out != NULL && \
			vars->tok[vars->i].outfile == NULL)
		{
			printf("syntax error near unexpected token\n");
			vars->tok_error = 1;
		}
		vars->i++;
	}
}
