/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:43:10 by mochan            #+#    #+#             */
/*   Updated: 2022/11/10 16:04:00 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	is_input_redirect_and_not_inside_quotes(t_prgm *vars, int j)
{	
	if (vars->tokens[vars->i].t_str[j] == '<' && \
	(is_between_quotes(vars->tokens[vars->i].t_str, '\'', j) == NULL && \
	is_between_quotes(vars->tokens[vars->i].t_str, '"', j) == NULL))
		return (1);
	else
		return (0);
}

int	is_heredoc_and_not_inside_quotes(t_prgm *vars, int j)
{
	if ((vars->tokens[vars->i].t_str[j - 1] == '<' && \
		vars->tokens[vars->i].t_str[j] == '<') && \
		(is_between_quotes(vars->tokens[vars->i].t_str, '\'', j - 1) == NULL \
		&& \
		is_between_quotes(vars->tokens[vars->i].t_str, '"', j - 1) == NULL) \
		&& \
		(is_between_quotes(vars->tokens[vars->i].t_str, '\'', j) == NULL \
		&& \
		is_between_quotes(vars->tokens[vars->i].t_str, '"', j) == NULL))
		return (1);
	else
		return (0);
}

int	count_input(t_prgm *vars)
{
	int	j;
	int	nb_input;

	j = 0;
	nb_input = 0;
	while (vars->tokens[vars->i].t_str[j] != '\0')
	{
		if (is_input_redirect_and_not_inside_quotes(vars, j))
			nb_input++;
		if (j > 0)
		{
			if (is_heredoc_and_not_inside_quotes(vars, j))
				nb_input--;
		}
		j++;
	}
	return (nb_input);
}
