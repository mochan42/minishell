/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_opt_arg_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:33:35 by mochan            #+#    #+#             */
/*   Updated: 2022/10/21 22:34:03 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	check_if_cmd_is_builtin(t_prgm *vr, int i)
{
	int	z;

	z = 0;
	while (z < 7)
	{
		if (ft_strncmp(*(ft_split(vr->tokens[i].cmd, ' ')), vr->builts[z], \
			ft_strlen(vr->builts[z])) == 0)
		{
			vr->tokens[i].built_in = 1;
			break ;
		}
		z++;
	}
}

void	extract_coa_at_string_start_both_redirections(t_prgm *vars)
{
	vars->ptr_coa = vars->tokens[vars->i].t_str;
	jump_white_spaces(vars);
	jump_cmd_opt_arg_input_redirect(vars);
	vars->tokens[vars->i].cmd = ft_substr(vars->ptr_coa, vars->start_coa, \
		vars->len_coa);
	printf("vars->tokens[%d].cmd :%s\n", vars->i, vars->tokens[vars->i].cmd);
}

void	extract_coa_at_string_middle_both_redirections(t_prgm *vars)
{
	vars->start_coa = 0;
	vars->len_coa = 0;
	vars->j = 0;
	jump_cmd_opt_arg_output_redirect(vars);
	vars->j--;
	vars->len_coa--;
	vars->tokens[vars->i].cmd = ft_substr(vars->ptr_coa, vars->start_coa, \
		vars->len_coa + 1);
	printf("vars->tokens[%d].cmd :%s\n", vars->i, vars->tokens[vars->i].cmd);
}

void	extract_cmd_opt_arg_both_redirections(t_prgm *vars)
{
	jump_white_spaces(vars);
	jump_infile(vars);
	jump_white_spaces(vars);
	if ((vars->j > 0 && vars->tokens[vars->i].t_str[vars->j] == '>' && \
		vars->tokens[vars->i].t_str[vars->j - 1] == '>') || \
		(vars->tokens[vars->i].t_str[vars->j] == '>'))
		extract_coa_at_string_start_both_redirections(vars);
	else
		extract_coa_at_string_middle_both_redirections(vars);
}

void	extract_cmd_opt_arg_input_redirection_only(t_prgm *vars)
{
	jump_white_spaces(vars);
	jump_infile(vars);
	jump_white_spaces(vars);
	vars->tokens[vars->i].cmd = ft_substr(vars->ptr_coa, 0, \
		ft_strlen(vars->ptr_coa));
	printf("vars->tokens[%d].cmd :%s\n", vars->i, vars->tokens[vars->i].cmd);
}
