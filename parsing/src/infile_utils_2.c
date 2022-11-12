/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:31:29 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 19:16:54 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	skip_white_spaces(t_prgm *vars, int *start, int cnt)
{
	while (vars->tok[cnt].t_str[*start] != '\0' && \
		(vars->tok[cnt].t_str[*start] == ' ' || \
		vars->tok[cnt].t_str[*start] == '\t'))
	{
		*start += 1;
	}
}

void	extract_infile_heredoc_and_fill_in_cmd_string(t_prgm *vars)
{
	vars->start = vars->j + 1;
	vars->tok[vars->i].in[vars->index] = IN_HEREDOC;
	skip_white_spaces(vars, &vars->start, vars->i);
	subs_infile(vars, &vars->start, vars->index);
	if (vars->tok_error == 1)
		return ;
	vars->index++;
	vars->j = vars->start;
	vars->tok[vars->i].cmd[vars->k++] = ' ';
}

void	extract_infile_input_redirect_and_fill_in_cmd_string(t_prgm *vars)
{
	vars->start = vars->j;
	vars->tok[vars->i].in[vars->index] = IN_REDIRECT;
	skip_white_spaces(vars, &vars->start, vars->i);
	subs_infile(vars, &vars->start, vars->index);
	if (vars->tok_error == 1)
		return ;
	vars->index++;
	vars->j = vars->start;
	vars->tok[vars->i].cmd[vars->k++] = ' ';
}

void	fill_in_cmd_string_no_infile(t_prgm *vars)
{
	if (vars->tok[vars->i].t_str[vars->j] != '<' || \
		(vars->tok[vars->i].t_str[vars->j] == '<' && \
		(is_btw_q(vars->tok[vars->i].t_str, '\'', vars->j) != NULL \
		|| is_btw_q(vars->tok[vars->i].t_str, '"', \
			vars->j) != NULL)) || \
		(vars->tok[vars->i].t_str[vars->j] == '>' && \
		(is_btw_q(vars->tok[vars->i].t_str, '\'', vars->j) != NULL \
		|| is_btw_q(vars->tok[vars->i].t_str, '"', \
			vars->j) != NULL)))
		vars->tok[vars->i].cmd[vars->k++] = \
			vars->tok[vars->i].t_str[vars->j];
	vars->j++;
}
