/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:27:23 by mochan            #+#    #+#             */
/*   Updated: 2022/10/22 22:04:19 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	find_infile_identify_input_redirection_type(t_prgm *vars)
{
	while (vars->j1 != -1)
	{
		if (vars->j1 > 0 && vars->tokens[vars->i1].t_str[vars->j1] == '<' && \
			vars->tokens[vars->i1].t_str[vars->j1 - 1] == '<')
		{
			vars->tokens[vars->i1].in = "<<";
			vars->j1++;
			vars->ptr_infile++;
			break ;
		}
		else if (vars->tokens[vars->i1].t_str[vars->j1] == '<')
		{
			vars->tokens[vars->i1].in = "<";
			vars->j1++;
			vars->ptr_infile++;
			break ;
		}
		else
		{
			vars->j1--;
			vars->ptr_infile--;
		}
	}
}

void	find_infile_extract_heredoc_infile(t_prgm *vars)
{
	while (vars->tokens[vars->i1].t_str[vars->j1] == ' ' || \
		vars->tokens[vars->i1].t_str[vars->j1] == '\t')
	{
		vars->j1++;
		vars->start_infile++;
	}
	while ((vars->tokens[vars->i1].t_str[vars->j1] != ' ' && \
		vars->tokens[vars->i1].t_str[vars->j1] != '\0'))
	{
		vars->j1++;
		vars->len_infile++;
	}
	vars->tokens[vars->i1].infile = ft_substr(vars->ptr_infile, \
		vars->start_infile, vars->len_infile);
	printf("input type[%d]= %s\n", vars->i1, vars->tokens[vars->j1].in);
	printf("infile[%d]=%s\n", vars->j1, vars->tokens[vars->j1].infile);
}

void	find_infile_extract_redirection_infile(t_prgm *vars)
{
	while (vars->tokens[vars->i1].t_str[vars->j1] == ' ' || \
		vars->tokens[vars->i1].t_str[vars->j1] == '\t')
	{
		vars->j1++;
		vars->start_infile++;
	}
	while ((vars->tokens[vars->i1].t_str[vars->j1] != ' ' && \
		vars->tokens[vars->i1].t_str[vars->j1] != '\0'))
	{
		vars->j1++;
		vars->len_infile++;
	}
	printf("input type[%d]= %s\n", vars->i1, vars->tokens[vars->i1].in);
	vars->tokens[vars->i1].infile = ft_substr(vars->ptr_infile, \
		vars->start_infile, vars->len_infile);
	printf("infile[%d]=%s\n", vars->i1, vars->tokens[vars->i1].infile);
}

void	find_infile_extract_infile(t_prgm *vars)
{
	if (vars->tokens[vars->i1].in != NULL && \
		ft_strncmp(vars->tokens[vars->i1].in, "<<", 2) == 0)
		find_infile_extract_heredoc_infile(vars);
	else if (vars->tokens[vars->i1].in != NULL && \
		ft_strncmp(vars->tokens[vars->i1].in, "<", 1) == 0)
		find_infile_extract_redirection_infile(vars);
}

void	find_infile(t_prgm *vars)
{
	vars->i1 = 0;
	while (vars->i1 < vars->pipe_ct + 1)
	{
		find_infile_init(vars);
		find_infile_go_to_string_end(vars);
		find_infile_identify_input_redirection_type(vars);
		find_infile_extract_infile(vars);
		printf("vars->tokens[%d].infile :%s\n", vars->i1, \
			vars->tokens[vars->i1].infile);
		vars->i1++;
	}
}
