/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:35:03 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 19:16:54 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	extract_outfile_append_and_fill_in_cmd_string(t_prgm *vars)
{
	vars->start = vars->j + 1;
	vars->tok[vars->i].out[vars->index] = OUT_APPEND;
	skip_white_spaces(vars, &vars->start, vars->i);
	subs_outfile(vars, &vars->start, vars->index);
	vars->index++;
	vars->j = vars->start;
	vars->tok[vars->i].cmd[vars->k++] = ' ';
}

void	extract_outfile_output_redirect_and_fill_in_cmd_string(t_prgm *vars)
{
	vars->start = vars->j;
	vars->tok[vars->i].out[vars->index] = OUT_REDIRECT;
	skip_white_spaces(vars, &vars->start, vars->i);
	subs_outfile(vars, &vars->start, vars->index);
	vars->index++;
	vars->j = vars->start;
	vars->tok[vars->i].cmd[vars->k++] = ' ';
}

void	fill_in_cmd_string_no_outfile(t_prgm *vars)
{
	if (vars->tok[vars->i].t_str[vars->j] != '>' || \
		(vars->tok[vars->i].t_str[vars->j] == '>' && \
		(is_btw_q(vars->tok[vars->i].t_str, '\'', \
			vars->j) != NULL \
		|| is_btw_q(vars->tok[vars->i].t_str, '"', \
			vars->j) != NULL)) || \
		(vars->tok[vars->i].t_str[vars->j] == '>' && \
		(is_btw_q(vars->tok[vars->i].t_str, '\'', \
			vars->j) != NULL \
		|| is_btw_q(vars->tok[vars->i].t_str, '"', \
			vars->j) != NULL)))
		vars->tok[vars->i].cmd[vars->k++] = \
			vars->tok[vars->i].t_str[vars->j];
	vars->j++;
}
