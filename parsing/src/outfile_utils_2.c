/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:35:03 by mochan            #+#    #+#             */
/*   Updated: 2022/11/11 12:27:19 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	extract_outfile_append_and_fill_in_cmd_string(t_prgm *vars)
{
	vars->start = vars->j + 1;
	vars->tokens[vars->i].out[vars->index] = OUT_APPEND;
	skip_white_spaces(vars, &vars->start, vars->i);
	subs_outfile(vars, &vars->start, vars->index);
	vars->index++;
	vars->j = vars->start;
	vars->tokens[vars->i].cmd[vars->k++] = ' ';
}

void	extract_outfile_output_redirect_and_fill_in_cmd_string(t_prgm *vars)
{
	vars->start = vars->j;
	vars->tokens[vars->i].out[vars->index] = OUT_REDIRECT;
	skip_white_spaces(vars, &vars->start, vars->i);
	subs_outfile(vars, &vars->start, vars->index);
	vars->index++;
	vars->j = vars->start;
	vars->tokens[vars->i].cmd[vars->k++] = ' ';
}

void	fill_in_cmd_string_no_outfile(t_prgm *vars)
{
	if (vars->tokens[vars->i].t_str[vars->j] != '>' || \
		(vars->tokens[vars->i].t_str[vars->j] == '>' && \
		(is_between_quotes(vars->tokens[vars->i].t_str, '\'', \
			vars->j) != NULL \
		|| is_between_quotes(vars->tokens[vars->i].t_str, '"', \
			vars->j) != NULL)) || \
		(vars->tokens[vars->i].t_str[vars->j] == '>' && \
		(is_between_quotes(vars->tokens[vars->i].t_str, '\'', \
			vars->j) != NULL \
		|| is_between_quotes(vars->tokens[vars->i].t_str, '"', \
			vars->j) != NULL)))
		vars->tokens[vars->i].cmd[vars->k++] = \
			vars->tokens[vars->i].t_str[vars->j];
	vars->j++;
}
