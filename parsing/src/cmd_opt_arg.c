/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_opt_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:26:25 by mochan            #+#    #+#             */
/*   Updated: 2022/10/22 18:35:28 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	find_cmd_opt_arg_both_redirections(t_prgm *vars)
{
	go_to_string_end(vars);
	go_to_beginning_cmd_opt_arg(vars);
	if ((vars->tokens[vars->i].in != NULL && \
		ft_strncmp(vars->tokens[vars->i].in, "<<", 2) == 0) || \
		(vars->tokens[vars->i].in != NULL && \
		ft_strncmp(vars->tokens[vars->i].in, "<", 1) == 0))
		extract_cmd_opt_arg_both_redirections(vars);
}

void	find_cmd_opt_arg_input_redirection_only(t_prgm *vars)
{
	go_to_string_end(vars);
	find_beginning_of_cmd_opt_arg(vars);
	if ((vars->tokens[vars->i].in != NULL && \
		ft_strncmp(vars->tokens[vars->i].in, "<<", 2) == 0) || \
		(vars->tokens[vars->i].in != NULL && \
		ft_strncmp(vars->tokens[vars->i].in, "<", 1) == 0))
		extract_cmd_opt_arg_input_redirection_only(vars);
}

void	find_cmd_opt_arg_output_redirection_only(t_prgm *vars)
{
	vars->len_coa = 0;
	jump_cmd_opt_arg_when_output_redirection_only(vars);
	printf("vars->tokens[%d].t_str[%d] :%c\n", vars->i, vars->j, \
		vars->tokens[vars->i].t_str[vars->j]);
	printf("len_coa = %d\n", vars->len_coa);
	vars->tokens[vars->i].cmd = ft_substr(vars->ptr_coa, 0, vars->len_coa);
	printf("vars->tokens[%d].cmd :%s\n", vars->i, vars->tokens[vars->i].cmd);
}

void	find_cmd_opt_arg_no_redirection_(t_prgm *vars)
{
	vars->start_coa = 0;
	jump_white_spaces(vars);
	vars->tokens[vars->i].cmd = ft_substr(vars->ptr_coa, vars->start_coa, \
		ft_strlen(vars->ptr_coa) - vars->start_coa);
	printf("vars->tokens[%d].cmd :%s\n", vars->i, vars->tokens[vars->i].cmd);
}

void	find_cmd_opt_arg(t_prgm *vars)
{
	vars->i = 0;
	while (vars->i < vars->pipe_ct + 1)
	{
		vars->j = 0;
		vars->ptr_coa = vars->tokens[vars->i].t_str;
		if (*vars->tokens[vars->i].in != '\0' && \
			*vars->tokens[vars->i].out != '\0')
			find_cmd_opt_arg_both_redirections(vars);
		else if (*vars->tokens[vars->i].in != '\0' && \
			*vars->tokens[vars->i].out == '\0')
			find_cmd_opt_arg_input_redirection_only(vars);
		else if (*vars->tokens[vars->i].in == '\0' && \
			*vars->tokens[vars->i].out != '\0')
			find_cmd_opt_arg_output_redirection_only(vars);
		else if (*vars->tokens[vars->i].in == '\0' && \
			*vars->tokens[vars->i].out == '\0')
			find_cmd_opt_arg_no_redirection_(vars);
		check_if_cmd_is_builtin(vars, vars->i);
		vars->i++;
	}
}
