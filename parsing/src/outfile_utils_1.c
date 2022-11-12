/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:34:28 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 19:16:54 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	is_output_redirect_and_not_inside_quotes(t_prgm *vars, int j)
{
	if (vars->tok[vars->i].t_str[j] == '>' && \
		(is_btw_q(vars->tok[vars->i].t_str, '\'', j) == NULL && \
		is_btw_q(vars->tok[vars->i].t_str, '"', j) == NULL))
		return (1);
	else
		return (0);
}

int	is_append_and_not_inside_quotes(t_prgm *vars, int j)
{
	if ((vars->tok[vars->i].t_str[j - 1] == '>' && \
		vars->tok[vars->i].t_str[j] == '>') && \
		(is_btw_q(vars->tok[vars->i].t_str, '\'', j - 1) == NULL && \
		is_btw_q(vars->tok[vars->i].t_str, '"', j - 1) == NULL) && \
		(is_btw_q(vars->tok[vars->i].t_str, '\'', j) == NULL && \
		is_btw_q(vars->tok[vars->i].t_str, '"', j) == NULL))
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
	while (vars->tok[vars->i].t_str[j] != '\0')
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
