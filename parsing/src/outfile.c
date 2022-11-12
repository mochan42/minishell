/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:41:28 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 12:21:28 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	subs_outfile(t_prgm *vars, int *start, int index)
{
	int	len_outfile;
	int	j;

	len_outfile = 0;
	j = *start;
	skip_white_spaces(vars, start, vars->i);
	while (vars->tokens[vars->i].t_str[j] != '\0' && \
		(vars->tokens[vars->i].t_str[j] != ' ' && \
		vars->tokens[vars->i].t_str[j] != '\t'))
	{
		if ((vars->tokens[vars->i].t_str[j] == '<' || \
			vars->tokens[vars->i].t_str[j] == '>')
			&& (is_between_quotes(vars->tokens[vars->i].t_str, '\'', j) == NULL \
			&& is_between_quotes(vars->tokens[vars->i].t_str, '"', j) == NULL))
		{
			vars->tok_error = 1;
			vars->tokens[vars->i].cmd[vars->k] = '\0';
			return ;
		}
		len_outfile++;
		j++;
	}
	if (vars->tokens[vars->i].outfile == NULL)
		return ;
	vars->tokens[vars->i].outfile[index] = trim_quotes \
		(ft_substr(vars->tokens[vars->i].t_str, *start, len_outfile++));
	if (*vars->tokens[vars->i].outfile[index] == '\0' && vars->tokens[vars->i].out[index] != OUT_STD)
		vars->tok_error = 1;
	*start += len_outfile - 1;
}

void	extract_outfiles_init(t_prgm *vars)
{
	vars->j = 0;
	vars->index = 0;
	vars->k = 0;
	vars->tokens[vars->i].nb_output = count_output(vars);
}

void	extract_outfiles(t_prgm *vars)
{
	extract_outfiles_init(vars);
	if (vars->tokens[vars->i].nb_output > 0)
	{
		vars->tokens[vars->i].out = malloc(sizeof(int) * \
			(vars->tokens[vars->i].nb_output + 1));
		vars->tokens[vars->i].outfile = malloc(sizeof(char *) * \
			(vars->tokens[vars->i].nb_output + 1));
		vars->tokens[vars->i].outfile[vars->tokens[vars->i].nb_output] = NULL;
	}
	while (vars->tokens[vars->i].t_str[vars->j] != '\0' && vars->tok_error != 1)
	{
		if (vars->j > 0)
		{
			if (is_append_and_not_inside_quotes(vars, vars->j))
				extract_outfile_append_and_fill_in_cmd_string(vars);
			else if (is_output_redirect_and_not_inside_quotes(vars, \
				vars->j - 1))
				extract_outfile_output_redirect_and_fill_in_cmd_string(vars);
			else
				fill_in_cmd_string_no_outfile(vars);
		}
		else
			fill_in_cmd_string_no_outfile(vars);
	}
	vars->tokens[vars->i].cmd[vars->k] = '\0';
}

void	find_outfile(t_prgm *vars)
{
	vars->i = 0;
	while (vars->i < vars->pipe_ct)
	{
		free(vars->tokens[vars->i].t_str);
		vars->tokens[vars->i].t_str = ft_strdup(vars->tokens[vars->i].cmd);
		free(vars->tokens[vars->i].cmd);
		vars->tokens[vars->i].cmd = malloc(sizeof(char) * \
			(ft_strlen(vars->tokens[vars->i].t_str) + 1));
		extract_outfiles(vars);
		if (vars->tokens[vars->i].out != NULL && \
			vars->tokens[vars->i].outfile == NULL)
		{
			printf("syntax error near unexpected token\n");
			vars->tok_error = 1;
		}
		vars->i++;
	}
}
