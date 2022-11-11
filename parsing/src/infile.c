/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:27:23 by mochan            #+#    #+#             */
/*   Updated: 2022/11/11 15:30:42 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	subs_infile(t_prgm *vars, int *start, int index)
{
	int	len_infile;
	int	j;

	len_infile = 0;
	j = *start;
	while (vars->tokens[vars->i].t_str[j] != '\0' && \
		(vars->tokens[vars->i].t_str[j] != ' ' && \
		vars->tokens[vars->i].t_str[j] != '\t'))
	{
		if ((vars->tokens[vars->i].t_str[j] == '<' || \
			vars->tokens[vars->i].t_str[j] == '>') && \
			(is_between_quotes(vars->tokens[vars->i].t_str, '\'', j) == NULL \
			&& \
			is_between_quotes(vars->tokens[vars->i].t_str, '"', j) == NULL))
		{
			vars->tok_error = 1;
			return ;
		}
		len_infile++;
		j++;
	}
	if (vars->tokens[vars->i].infile == NULL)
		return ;
	vars->tokens[vars->i].infile[index] = trim_quotes \
	(ft_substr(vars->tokens[vars->i].t_str, *start, len_infile++));
	if (*vars->tokens[vars->i].infile[index] == '\0' && vars->tokens[vars->i].in[index] != IN_STD)
		vars->tok_error = 1;
	*start += len_infile - 1;
}

void	extract_infiles_init(t_prgm *vars)
{
	if (vars->tokens[vars->i].nb_input > 0)
	{
		vars->tokens[vars->i].in = malloc(sizeof(int) * \
			(vars->tokens[vars->i].nb_input + 1));
		vars->tokens[vars->i].infile = malloc(sizeof(char *) * \
			(vars->tokens[vars->i].nb_input + 1));
		vars->tokens[vars->i].infile[vars->tokens[vars->i].nb_input] = NULL;
	}
}

void	extract_infiles(t_prgm *vars)
{
	vars->tokens[vars->i].nb_input = count_input(vars);
	extract_infiles_init(vars);
	vars->index = 0;
	vars->k = 0;
	vars->j = 0;
	vars->start = 0;
	while (vars->tokens[vars->i].t_str[vars->j] != '\0' && \
		vars->tok_error != 1)
	{
		if (vars->j > 0)
		{
			if (is_heredoc_and_not_inside_quotes(vars, vars->j))
				extract_infile_heredoc_and_fill_in_cmd_string(vars);
			else if (is_input_redirect_and_not_inside_quotes(vars, vars->j - 1))
				extract_infile_input_redirect_and_fill_in_cmd_string(vars);
			else
				fill_in_cmd_string_no_infile(vars);
		}
		else
			fill_in_cmd_string_no_infile(vars);
	}
}

void	find_infile(t_prgm *vars)
{
	vars->i = 0;
	while (vars->i < vars->pipe_ct)
	{
		vars->tokens[vars->i].cmd = malloc(sizeof(char) * \
			(ft_strlen(vars->tokens[vars->i].t_str) + 1));
		extract_infiles(vars);
		if ((vars->tokens[vars->i].in != NULL && \
			vars->tokens[vars->i].infile == NULL) || vars->tok_error == 1)
			vars->tok_error = 1;
		vars->i++;
	}
}
