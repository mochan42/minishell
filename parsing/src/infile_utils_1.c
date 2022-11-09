/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:43:10 by mochan            #+#    #+#             */
/*   Updated: 2022/11/09 22:15:29 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	find_infile_init(t_prgm *vars)
{
	vars->j1 = 0;
	vars->start_infile = 0;
	vars->len_infile = 0;
}

void	find_infile_go_to_string_end(t_prgm *vars)
{
	while (vars->tokens[vars->i1].t_str[vars->j1] != '\0')
	{
		vars->j1++;
		vars->ptr_infile++;
	}
}
