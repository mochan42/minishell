/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_opt_arg_utils_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:28:59 by mochan            #+#    #+#             */
/*   Updated: 2022/10/23 14:27:03 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	extract_cmd_opt_arg_start_input_redirection_only(t_prgm *vars)
{
	vars->j = vars->start_coa;
	vars->len_coa = 0;
	printf("token[%d] ptr_coa :%s\n", vars->i, vars->ptr_coa);
	printf("vars->tokens[%d].t_str :%s\n", vars->i, vars->tokens[vars->i].t_str);
	while (vars->tokens[vars->i].t_str[vars->j] != '<')
	{
		vars->len_coa++;
		vars->j++;
	}
	vars->tokens[vars->i].cmd = ft_substr(vars->ptr_coa, vars->start_coa, \
		vars->len_coa);
	printf("vars->tokens[%d].cmd :%s\n", vars->i, vars->tokens[vars->i].cmd);
}
