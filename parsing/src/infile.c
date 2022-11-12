/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:27:23 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 19:16:54 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	subs_infile(t_prgm *v, int *start, int index)
{
	int	len_infile;
	int	j;

	len_infile = 0;
	j = *start;
	while (v->tok[v->i].t_str[j] != '\0' && \
		(v->tok[v->i].t_str[j] != ' ' && v->tok[v->i].t_str[j] != '\t'))
	{
		if ((v->tok[v->i].t_str[j] == '<' || v->tok[v->i].t_str[j] == '>') \
			&& (is_btw_q(v->tok[v->i].t_str, '\'', j) == NULL \
			&& is_btw_q(v->tok[v->i].t_str, '"', j) == NULL))
		{
			v->tok_error = 1;
			return ;
		}
		len_infile++;
		j++;
	}
	if (v->tok[v->i].infile == NULL)
		return ;
	v->tok[v->i].infile[index] = trim_quotes \
	(ft_substr(v->tok[v->i].t_str, *start, len_infile++));
	if (*v->tok[v->i].infile[index] == '\0' && v->tok[v->i].in[index] != IN_STD)
		v->tok_error = 1;
	*start += len_infile - 1;
}

void	extract_infiles_init(t_prgm *vars)
{
	if (vars->tok[vars->i].nb_input > 0)
	{
		vars->tok[vars->i].in = malloc(sizeof(int) * \
			(vars->tok[vars->i].nb_input + 1));
		vars->tok[vars->i].infile = malloc(sizeof(char *) * \
			(vars->tok[vars->i].nb_input + 1));
		vars->tok[vars->i].infile[vars->tok[vars->i].nb_input] = NULL;
	}
}

void	extract_infiles(t_prgm *vars)
{
	vars->tok[vars->i].nb_input = count_input(vars);
	extract_infiles_init(vars);
	vars->index = 0;
	vars->k = 0;
	vars->j = 0;
	vars->start = 0;
	while (vars->tok[vars->i].t_str[vars->j] != '\0' && \
		vars->tok_error != 1)
	{
		if (vars->j > 0)
		{
			if (is_heredoc_and_not_inside_quotes(vars, vars->j))
				extract_infile_heredoc_and_fill_in_cmd_string(vars);
			else if (is_input_redirect_and_not_inside_quotes(vars, vars->j - 1))
				extract_infile_input_redirect_and_fill_in_cmd_string(vars);
			else
				fill_in_cmd_string_no_infile(vars);
		}
		else
			fill_in_cmd_string_no_infile(vars);
	}
	vars->tok[vars->i].cmd[vars->k] = '\0';
}

void	find_infile(t_prgm *vars)
{
	vars->i = 0;
	while (vars->i < vars->pipe_ct)
	{
		vars->tok[vars->i].cmd = malloc(sizeof(char) * \
			(ft_strlen(vars->tok[vars->i].t_str) + 1));
		extract_infiles(vars);
		if ((vars->tok[vars->i].in != NULL && \
			vars->tok[vars->i].infile == NULL) || vars->tok_error == 1)
			vars->tok_error = 1;
		vars->i++;
	}
}
