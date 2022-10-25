/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_opt_arg_utils_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:28:59 by mochan            #+#    #+#             */
/*   Updated: 2022/10/25 19:12:29 by mochan           ###   ########.fr       */
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

void	jump_output_redirection_sign(t_prgm *vars)
{
	while (vars->tokens[vars->i].t_str[vars->j] == '>')
	{
		vars->start_coa++;
		vars->j++;
		vars->ptr_coa++;
	}
}

void	jump_outfile(t_prgm *vars)
{
	while ((vars->tokens[vars->i].t_str[vars->j] != ' ' && \
		vars->tokens[vars->i].t_str[vars->j] != '\0'))
	{
		vars->j++;
		vars->ptr_coa++;
	}
}

void	extract_cmd_opt_arg_start_output_redirection_only(t_prgm *vars)
{
	vars->start_coa = 0;
	jump_output_redirection_sign(vars);
	jump_white_spaces(vars, "ptr_coa");
	jump_outfile(vars);
	jump_white_spaces(vars, "ptr_coa");
	while (vars->tokens[vars->i].t_str[vars->j] != '\0')
	{
		vars->len_coa++;
		vars->j++;
	}
	vars->tokens[vars->i].cmd = ft_substr(vars->ptr_coa, 0, vars->len_coa);
	printf("vars->tokens[%d].cmd :%s\n", vars->i, vars->tokens[vars->i].cmd);
}

void	extract_cmd_opt_arg_start_both_redirections_out2in(t_prgm *vars)
{
	vars->start_coa = 0;
	vars->len_coa = 0;
	jump_output_redirection_sign(vars);
	jump_white_spaces(vars, "ptr_coa");
	jump_outfile(vars);
	jump_white_spaces(vars, "ptr_coa");
	while (vars->tokens[vars->i].t_str[vars->j] != '<')
	{
		vars->len_coa++;
		vars->j++;
	}
	vars->tokens[vars->i].cmd = ft_substr(vars->ptr_coa, 0, vars->len_coa);
	printf("vars->tokens[%d].cmd :%s\n", vars->i, vars->tokens[vars->i].cmd);
}
