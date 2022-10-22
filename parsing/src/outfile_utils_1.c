/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:34:28 by mochan            #+#    #+#             */
/*   Updated: 2022/10/22 16:34:46 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	find_outfile_init(t_prgm *vars)
{
	vars->j2 = 0;
	vars->start_outfile = 0;
	vars->len_outfile = 0;
	vars->ptr_outfile = vars->tokens[vars->i2].t_str;
}

void	find_outfile_go_to_string_end(t_prgm *vars)
{
	while (vars->tokens[vars->i2].t_str[vars->j2] != '\0')
	{
		vars->j2++;
		vars->ptr_outfile++;
	}
}
