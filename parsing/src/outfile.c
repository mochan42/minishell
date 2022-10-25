/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:41:28 by mochan            #+#    #+#             */
/*   Updated: 2022/10/25 18:57:17 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	find_outfile_identify_output_redirection_type(t_prgm *vars)
{
	while (vars->j2 >= 0)
	{
		if (vars->j2 > 0 && vars->tokens[vars->i2].t_str[vars->j2] == '>' && \
			vars->tokens[vars->i2].t_str[vars->j2 - 1] == '>')
		{
			vars->tokens[vars->i2].out = ">>";
			vars->j2++;
			vars->ptr_outfile++;
			break ;
		}
		else if (vars->tokens[vars->i2].t_str[vars->j2] == '>')
		{
			vars->tokens[vars->i2].out = ">";
			vars->j2++;
			vars->ptr_outfile++;
			break ;
		}
		else
		{
			vars->j2--;
			vars->ptr_outfile--;
		}
	}
}

void	find_outfile_extract_heredoc_outfile(t_prgm *vars)
{
	while (vars->tokens[vars->i2].t_str[vars->j2] == ' ' || \
		vars->tokens[vars->i2].t_str[vars->j2] == '\t')
	{
		vars->j2++;
		vars->start_outfile++;
	}
	while ((vars->tokens[vars->i2].t_str[vars->j2] != ' ' && \
		vars->tokens[vars->i2].t_str[vars->j2] != '\0'))
	{
		vars->j2++;
		vars->len_outfile++;
	}
	vars->tokens[vars->i2].outfile = ft_substr(vars->ptr_outfile, \
		vars->start_outfile, vars->len_outfile);
}

void	find_outfile_extract_redirection_outfile(t_prgm *vars)
{
	while (vars->tokens[vars->i2].t_str[vars->j2] == ' ' || \
		vars->tokens[vars->i2].t_str[vars->j2] == '\t')
	{
		vars->j2++;
		vars->start_outfile++;
	}
	while ((vars->tokens[vars->i2].t_str[vars->j2] != ' ' && \
		vars->tokens[vars->i2].t_str[vars->j2] != '\0'))
	{
		vars->j2++;
		vars->len_outfile++;
	}
	vars->tokens[vars->i2].outfile = ft_substr(vars->ptr_outfile, \
		vars->start_outfile, vars->len_outfile);
}

void	find_outfile_extract_outfile(t_prgm *vars)
{
	if (vars->tokens[vars->i2].out != NULL && \
		ft_strncmp(vars->tokens[vars->i2].out, ">>", 2) == 0)
		find_outfile_extract_heredoc_outfile(vars);
	else if (vars->tokens[vars->i2].out != NULL && \
		ft_strncmp(vars->tokens[vars->i2].out, ">", 1) == 0)
		find_outfile_extract_redirection_outfile(vars);
}

void	find_outfile(t_prgm *vars)
{
	vars->i2 = 0;
	while (vars->i2 < vars->pipe_ct + 1)
	{
		find_outfile_init(vars);
		find_outfile_go_to_string_end(vars);
		find_outfile_identify_output_redirection_type(vars);
		find_outfile_extract_outfile(vars);
		printf("vars->tokens[%d].outfile :%s\n", vars->i2, \
			vars->tokens[vars->i2].outfile);
		vars->i2++;
	}
}
