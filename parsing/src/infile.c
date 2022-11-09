/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:27:23 by mochan            #+#    #+#             */
/*   Updated: 2022/11/09 21:00:22 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// void	find_infile_identify_input_redirection_type(t_prgm *vars)
// {
// 	while (vars->j1 != -1)
// 	{
// 		if (vars->j1 > 0 && vars->tokens[vars->i1].t_str[vars->j1] == '<' && \
// 			vars->tokens[vars->i1].t_str[vars->j1 - 1] == '<')
// 		{
// 			vars->tokens[vars->i1].in = IN_HEREDOC;
// 			vars->j1++;
// 			vars->ptr_infile++;
// 			break ;
// 		}
// 		else if (vars->tokens[vars->i1].t_str[vars->j1] == '<')
// 		{
// 			vars->tokens[vars->i1].in = IN_REDIRECT;
// 			vars->j1++;
// 			vars->ptr_infile++;
// 			break ;
// 		}
// 		else
// 		{
// 			vars->j1--;
// 			vars->ptr_infile--;
// 		}
// 	}
// }

// void	find_infile_extract_heredoc_infile(t_prgm *vars)
// {
// 	while (vars->tokens[vars->i1].t_str[vars->j1] == ' ' || \
// 		vars->tokens[vars->i1].t_str[vars->j1] == '\t')
// 	{
// 		vars->j1++;
// 		vars->start_infile++;
// 	}
// 	while ((vars->tokens[vars->i1].t_str[vars->j1] != ' ' && \
// 		vars->tokens[vars->i1].t_str[vars->j1] != '\0'))
// 	{
// 		vars->j1++;
// 		vars->len_infile++;
// 	}
// 	vars->tokens[vars->i1].infile = ft_substr(vars->ptr_infile, \
// 		vars->start_infile, vars->len_infile);
// 	printf("input type[%d]= %d\n", vars->i1, vars->tokens[vars->j1].in);
// 	printf("infile[%d]=%s\n", vars->j1, vars->tokens[vars->j1].infile);
// }

// void	find_infile_extract_redirection_infile(t_prgm *vars)
// {
// 	while (vars->tokens[vars->i1].t_str[vars->j1] == ' ' || \
// 		vars->tokens[vars->i1].t_str[vars->j1] == '\t')
// 	{
// 		vars->j1++;
// 		vars->start_infile++;
// 	}
// 	while ((vars->tokens[vars->i1].t_str[vars->j1] != ' ' && \
// 		vars->tokens[vars->i1].t_str[vars->j1] != '\0'))
// 	{
// 		vars->j1++;
// 		vars->len_infile++;
// 	}
// 	printf("input type[%d]= %d\n", vars->i1, vars->tokens[vars->i1].in);
// 	vars->tokens[vars->i1].infile = ft_substr(vars->ptr_infile, \
// 		vars->start_infile, vars->len_infile);
// 	printf("infile[%d]=%s\n", vars->i1, vars->tokens[vars->i1].infile);
// }

// void	find_infile_extract_infile(t_prgm *vars)
// {
// 	if (vars->tokens[vars->i1].in != IN_STD && \
// 		vars->tokens[vars->i1].in == IN_HEREDOC)
// 		find_infile_extract_heredoc_infile(vars);
// 	else if (vars->tokens[vars->i1].in != IN_STD && \
// 		vars->tokens[vars->i1].in == IN_REDIRECT)
// 		find_infile_extract_redirection_infile(vars);
// }

int	count_input(t_prgm *vars)
{
	int	j;
	int	nb_input;

	j = 0;
	nb_input = 0;
	while(vars->tokens[vars->i1].t_str[j] != '\0')
	{
		if (vars->tokens[vars->i1].t_str[j] == '<' && \
			(is_between_quotes(vars->tokens[vars->i1].t_str, '\'',j) == NULL && \
			 is_between_quotes(vars->tokens[vars->i1].t_str, '"',j) == NULL))
			nb_input++;
		if (j > 0)
		{
			if ((vars->tokens[vars->i1].t_str[j - 1] == '<' && vars->tokens[vars->i1].t_str[j] == '<') &&\
				(is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j - 1) == NULL && \
				 is_between_quotes(vars->tokens[vars->i1].t_str, '"', j - 1) == NULL) && \
				 (is_between_quotes(vars->tokens[vars->i1].t_str, '\'',j) == NULL && \
			 		is_between_quotes(vars->tokens[vars->i1].t_str, '"',j) == NULL)
				)
				nb_input--;
		}
		j++;
	}
	return(nb_input);
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
	int len_infile;
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
	vars->tokens[vars->i1].infile[index] = ft_substr(vars->tokens[vars->i1].t_str, *start, len_infile++);
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
			if ((vars->tokens[vars->i1].t_str[j] == '<' && vars->tokens[vars->i1].t_str[j - 1] == '<')\
				&& ((is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j - 1) == NULL && \
				is_between_quotes(vars->tokens[vars->i1].t_str, '"', j - 1) == NULL) && \
				(is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j) == NULL && \
			 	is_between_quotes(vars->tokens[vars->i1].t_str, '"', j) == NULL)))
			{
				start = j+1;
				vars->tokens[vars->i1].in[index] = IN_HEREDOC;
				skip_white_spaces(vars, &start, vars->i1);
				subs_infile(vars, &start, index);
				index++;
				j = start;
				vars->tokens[vars->i1].cmd[k++] = ' ';
			}
			else if (vars->tokens[vars->i1].t_str[j - 1] == '<' && \
						(is_between_quotes(vars->tokens[vars->i1].t_str, '\'',j - 1) == NULL && \
			 			is_between_quotes(vars->tokens[vars->i1].t_str, '"',j - 1) == NULL))
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
					(vars->tokens[vars->i1].t_str[j] == '<' && 
					(is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j) != NULL \
					|| is_between_quotes(vars->tokens[vars->i1].t_str, '"', j) != NULL)))
					vars->tokens[vars->i1].cmd[k++] = vars->tokens[vars->i1].t_str[j];
				// printf("\t 1 else vars->tokens[%d].t_str[%d]	:%c\n", vars->i1, j, vars->tokens[vars->i1].t_str[j]);
				j++;
			}
		}
		else
		{
			if (vars->tokens[vars->i1].t_str[j] != '<' || \
				(vars->tokens[vars->i1].t_str[j] == '<' && 
				(is_between_quotes(vars->tokens[vars->i1].t_str, '\'', j) != NULL \
				|| is_between_quotes(vars->tokens[vars->i1].t_str, '"', j) != NULL)))
				vars->tokens[vars->i1].cmd[k++] = vars->tokens[vars->i1].t_str[j];
			// printf("2 else vars->tokens[%d].t_str[%d]	:%c\n", vars->i1, j, vars->tokens[vars->i1].t_str[j]);
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
		// find_infile_go_to_string_end(vars);
		// find_infile_identify_input_redirection_type(vars);
		// find_infile_extract_infile(vars);
		// printf("vars->tokens[%d].infile :%s\n", vars->i1,
		// 	vars->tokens[vars->i1].infile);
		vars->i1++;
	}
}
