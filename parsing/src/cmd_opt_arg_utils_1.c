/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_opt_arg_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:31:09 by mochan            #+#    #+#             */
/*   Updated: 2022/10/21 22:31:41 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	go_to_string_end(t_prgm *vars)
{
	while (vars->tokens[vars->i].t_str[vars->j] != '\0')
	{
		vars->j++;
		vars->ptr_coa++;
	}
}

// - if statment : look for infile here doc and jump it
// - else if statement : look for infile redirection and jump it
// - else statement : continue to go to beginning of cmd line string
// while input redirection is not found.
void	go_to_beginning_cmd_opt_arg(t_prgm *vars)
{
	while (vars->j != -1)
	{
		if (vars->j > 0 && vars->tokens[vars->i].t_str[vars->j] == '<' && \
			vars->tokens[vars->i].t_str[vars->j - 1] == '<')
		{
			vars->tokens[vars->i].in = "<<";
			vars->j++;
			vars->ptr_coa++;
			break ;
		}
		else if (vars->tokens[vars->i].t_str[vars->j] == '<')
		{
			vars->tokens[vars->i].in = "<";
			vars->j++;
			vars->ptr_coa++;
			break ;
		}
		else
		{
			vars->j--;
			vars->ptr_coa--;
		}
	}
}

void	jump_white_spaces(t_prgm *vars)
{
	while (vars->tokens[vars->i].t_str[vars->j] == ' ' || \
		vars->tokens[vars->i].t_str[vars->j] == '\t')
	{
		vars->j++;
		vars->ptr_coa++;
	}
}

void	jump_infile(t_prgm *vars)
{
	while ((vars->tokens[vars->i].t_str[vars->j] != ' ' && \
		vars->tokens[vars->i].t_str[vars->j] != '\0'))
	{
		vars->j++;
		vars->ptr_coa++;
	}
}

void	jump_cmd_opt_arg_input_redirect(t_prgm *vars)
{
	vars->start_coa = 0;
	vars->len_coa = 0;
	vars->j = 0;
	while ((vars->ptr_coa[vars->j] != '<' && vars->ptr_coa[vars->j] != '\0'))
	{
		vars->j++;
		vars->len_coa++;
	}
}
