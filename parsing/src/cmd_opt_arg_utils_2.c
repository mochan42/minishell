/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_opt_arg_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:32:35 by mochan            #+#    #+#             */
/*   Updated: 2022/10/21 22:32:53 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	jump_cmd_opt_arg_output_redirect(t_prgm *vars)
{
	while ((vars->ptr_coa[vars->j] != '>' && vars->ptr_coa[vars->j] != '\0'))
	{
		vars->j++;
		vars->len_coa++;
	}
}

void	move_forward_by_one_char(t_prgm *vars)
{
	vars->j++;
	vars->ptr_coa++;
}

void	move_backwards_by_one_char(t_prgm *vars)
{
	vars->j--;
	vars->ptr_coa--;
}

// - 1st if : look for << heredoc and jump it
// - 2nd if : look for < input redirection and jump it
// - else if : look for infile redirection and jump it
// - else : continue to go to beginning of cmd line string while
// input redirection is not found.
void	find_beginning_of_cmd_opt_arg(t_prgm *vars)
{
	while (vars->j != -1)
	{
		if (vars->j > 0 && vars->tokens[vars->i].t_str[vars->j] == '<' && \
			vars->tokens[vars->i].t_str[vars->j - 1] == '<')
		{
			vars->tokens[vars->i].in = "<<";
			move_forward_by_one_char(vars);
			break ;
		}
		if (vars->j > 0 && vars->tokens[vars->i].t_str[vars->j] == '<' && \
		vars->tokens[vars->i].t_str[vars->j - 1] == '<')
		{
			vars->tokens[vars->i].in = "<<";
			move_forward_by_one_char(vars);
			break ;
		}
		else if (vars->tokens[vars->i].t_str[vars->j] == '<')
		{
			vars->tokens[vars->i].in = "<";
			move_forward_by_one_char(vars);
			break ;
		}
		else
			move_backwards_by_one_char(vars);
	}
}

// jump cmd arg opt in case there is only output redirection
void	jump_cmd_opt_arg_when_output_redirection_only(t_prgm *vars)
{
	while (vars->tokens[vars->i].t_str[vars->j] != '>')
	{
		vars->j++;
		vars->len_cmd++;
	}
}
