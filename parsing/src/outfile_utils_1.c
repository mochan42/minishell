/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:34:28 by mochan            #+#    #+#             */
/*   Updated: 2022/11/10 17:00:35 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	is_output_redirect_and_not_inside_quotes(t_prgm *vars, int j)
{
	if (vars->tokens[vars->i].t_str[j] == '>' && \
		(is_between_quotes(vars->tokens[vars->i].t_str, '\'', j) == NULL && \
		is_between_quotes(vars->tokens[vars->i].t_str, '"', j) == NULL))
		return (1);
	else
		return (0);
}

int	is_append_and_not_inside_quotes(t_prgm *vars, int j)
{
	if ((vars->tokens[vars->i].t_str[j - 1] == '>' && \
		vars->tokens[vars->i].t_str[j] == '>') && \
		(is_between_quotes(vars->tokens[vars->i].t_str, '\'', j - 1) == NULL && \
		is_between_quotes(vars->tokens[vars->i].t_str, '"', j - 1) == NULL) && \
		(is_between_quotes(vars->tokens[vars->i].t_str, '\'', j) == NULL && \
		is_between_quotes(vars->tokens[vars->i].t_str, '"', j) == NULL))
		return (1);
	else
		return (0);
}

int	count_output(t_prgm *vars)
{
	int	j;
	int	nb_output;

	j = 0;
	nb_output = 0;
	while (vars->tokens[vars->i].t_str[j] != '\0')
	{
		if (is_output_redirect_and_not_inside_quotes(vars, j))
			nb_output++;
		if (j > 0)
		{
			if (is_append_and_not_inside_quotes(vars, j))
				nb_output--;
		}
		j++;
	}
	return (nb_output);
}
