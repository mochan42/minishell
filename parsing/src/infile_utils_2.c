/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:31:29 by mochan            #+#    #+#             */
/*   Updated: 2022/11/11 12:48:08 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	skip_white_spaces(t_prgm *vars, int *start, int cnt)
{
	while (vars->tokens[cnt].t_str[*start] != '\0' && \
		(vars->tokens[cnt].t_str[*start] == ' ' || \
		vars->tokens[cnt].t_str[*start] == '\t'))
	{
		*start += 1;
	}
}

void	extract_infile_heredoc_and_fill_in_cmd_string(t_prgm *vars)
{
	vars->start = vars->j + 1;
	vars->tokens[vars->i].in[vars->index] = IN_HEREDOC;
	skip_white_spaces(vars, &vars->start, vars->i);
	subs_infile(vars, &vars->start, vars->index);
	if (vars->tok_error == 1)
		return ;
	vars->index++;
	vars->j = vars->start;
	vars->tokens[vars->i].cmd[vars->k++] = ' ';
}

void	extract_infile_input_redirect_and_fill_in_cmd_string(t_prgm *vars)
{
	vars->start = vars->j;
	vars->tokens[vars->i].in[vars->index] = IN_REDIRECT;
	skip_white_spaces(vars, &vars->start, vars->i);
	subs_infile(vars, &vars->start, vars->index);
	if (vars->tok_error == 1)
		return ;
	vars->index++;
	vars->j = vars->start;
	vars->tokens[vars->i].cmd[vars->k++] = ' ';
}

void	fill_in_cmd_string_no_infile(t_prgm *vars)
{
	if (vars->tokens[vars->i].t_str[vars->j] != '<' || \
		(vars->tokens[vars->i].t_str[vars->j] == '<' && \
		(is_between_quotes(vars->tokens[vars->i].t_str, '\'', vars->j) != NULL \
		|| is_between_quotes(vars->tokens[vars->i].t_str, '"', \
			vars->j) != NULL)) || \
		(vars->tokens[vars->i].t_str[vars->j] == '>' && \
		(is_between_quotes(vars->tokens[vars->i].t_str, '\'', vars->j) != NULL \
		|| is_between_quotes(vars->tokens[vars->i].t_str, '"', \
			vars->j) != NULL)))
		vars->tokens[vars->i].cmd[vars->k++] = \
			vars->tokens[vars->i].t_str[vars->j];
	vars->j++;
}
