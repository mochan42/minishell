/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:27:23 by mochan            #+#    #+#             */
/*   Updated: 2022/11/09 22:58:29 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	count_input(t_prgm *vars)
{
	int	j;
	int	nb_input;

	j = 0;
	nb_input = 0;
	while (vars->tokens[vars->i1].t_str[j] != '\0')
	{
		if (vars->tokens[vars->i1].t_str[j] == '<' && \
			(is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j) == NULL && \
			is_between_quotes(vars->tokens[vars->i1].t_str, '"', j) == NULL))
			nb_input++;
		if (j > 0)
		{
			if ((vars->tokens[vars->i1].t_str[j - 1] == '<' && vars->tokens[vars->i1].t_str[j] == '<') && \
				(is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j - 1) == NULL && \
				is_between_quotes(vars->tokens[vars->i1].t_str, '"', j - 1) == NULL) && \
				(is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j) == NULL && \
				is_between_quotes(vars->tokens[vars->i1].t_str, '"', j) == NULL))
				nb_input--;
		}
		j++;
	}
	return (nb_input);
}

void	skip_white_spaces(t_prgm *vars, int *start, int cnt)
{
	while (vars->tokens[cnt].t_str[*start] != '\0' && (vars->tokens[cnt].t_str[*start] == ' ' || vars->tokens[cnt].t_str[*start] == '\t'))
	{
		*start += 1;
	}
}

void	subs_infile(t_prgm *vars, int *start, int index)
{
	int	len_infile;
	int	j;

	len_infile = 0;
	j = *start;
	skip_white_spaces(vars, start, vars->i1);
	while (vars->tokens[vars->i1].t_str[j] != '\0' && (vars->tokens[vars->i1].t_str[j] != ' ' && vars->tokens[vars->i1].t_str[j] != '\t'))
	{
		if ((vars->tokens[vars->i1].t_str[j] == '<' || vars->tokens[vars->i1].t_str[j] == '>')
			&& (is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j) == NULL
			&& is_between_quotes(vars->tokens[vars->i1].t_str, '"', j) == NULL))
		{
			vars->tok_error = 1;
			return ;
		}
		len_infile++;
		j++;
	}
	vars->tokens[vars->i1].infile[index] = trim_quotes(ft_substr(vars->tokens[vars->i1].t_str, *start, len_infile++));
	*start += len_infile - 1;
}

void	extract_infiles(t_prgm *vars)
{
	int	start;
	int	j;
	int	index;
	int	k;

	vars->tokens[vars->i1].nb_input = count_input(vars);
	if (vars->tokens[vars->i1].nb_input > 0)
	{
		vars->tokens[vars->i1].in = malloc(sizeof(int) * (vars->tokens[vars->i1].nb_input + 1));
		vars->tokens[vars->i1].infile = malloc(sizeof(char *) * (vars->tokens[vars->i1].nb_input + 1));
		vars->tokens[vars->i1].infile[vars->tokens[vars->i1].nb_input] = NULL;
	}
	index = 0;
	k = 0;
	j = 0;
	start = 0;
	while (vars->tokens[vars->i1].t_str[j] != '\0' && vars->tok_error != 1)
	{
		if (j > 0)
		{
			if ((vars->tokens[vars->i1].t_str[j] == '<' && vars->tokens[vars->i1].t_str[j - 1] == '<') \
				&& ((is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j - 1) == NULL && \
				is_between_quotes(vars->tokens[vars->i1].t_str, '"', j - 1) == NULL) && \
				(is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j) == NULL && \
				is_between_quotes(vars->tokens[vars->i1].t_str, '"', j) == NULL)))
			{
				start = j + 1;
				vars->tokens[vars->i1].in[index] = IN_HEREDOC;
				skip_white_spaces(vars, &start, vars->i1);
				subs_infile(vars, &start, index);
				index++;
				j = start;
				vars->tokens[vars->i1].cmd[k++] = ' ';
			}
			else if (vars->tokens[vars->i1].t_str[j - 1] == '<' && \
						(is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j - 1) == NULL && \
						is_between_quotes(vars->tokens[vars->i1].t_str, '"', j - 1) == NULL))
			{
				start = j;
				vars->tokens[vars->i1].in[index] = IN_REDIRECT;
				skip_white_spaces(vars, &start, vars->i1);
				subs_infile(vars, &start, index);
				index++;
				j = start;
				vars->tokens[vars->i1].cmd[k++] = ' ';
			}
			else
			{
				if (vars->tokens[vars->i1].t_str[j] != '<' || \
					(vars->tokens[vars->i1].t_str[j] == '<' && \
					(is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j) != NULL \
					|| is_between_quotes(vars->tokens[vars->i1].t_str, '"', j) != NULL)))
					vars->tokens[vars->i1].cmd[k++] = vars->tokens[vars->i1].t_str[j];
				j++;
			}
		}
		else
		{
			if (vars->tokens[vars->i1].t_str[j] != '<' || \
				(vars->tokens[vars->i1].t_str[j] == '<' && \
				(is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j) != NULL \
				|| is_between_quotes(vars->tokens[vars->i1].t_str, '"', j) != NULL)))
				vars->tokens[vars->i1].cmd[k++] = vars->tokens[vars->i1].t_str[j];
			j++;
		}
	}
	vars->tokens[vars->i1].cmd[k] = '\0';
}

void	find_infile(t_prgm *vars)
{
	vars->i1 = 0;
	while (vars->i1 < vars->pipe_ct + 1)
	{
		vars->tokens[vars->i1].cmd = malloc(sizeof(char) * (ft_strlen(vars->tokens[vars->i1].t_str) + 1));
		find_infile_init(vars);
		extract_infiles(vars);
		if ((vars->tokens[vars->i1].in != NULL && vars->tokens[vars->i1].infile == NULL) || vars->tok_error == 1)
			vars->tok_error = 1;
		vars->i1++;
	}
}
