/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:41:28 by mochan            #+#    #+#             */
/*   Updated: 2022/11/08 17:37:39 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// void	find_outfile_identify_output_redirection_type(t_prgm *vars)
// {
// 	while (vars->j2 >= 0)
// 	{
// 		if (vars->j2 > 0 && vars->tokens[vars->i2].t_str[vars->j2] == '>' && \
// 			vars->tokens[vars->i2].t_str[vars->j2 - 1] == '>')
// 		{
// 			vars->tokens[vars->i2].out = OUT_APPEND;
// 			vars->j2++;
// 			vars->ptr_outfile++;
// 			break ;
// 		}
// 		else if (vars->tokens[vars->i2].t_str[vars->j2] == '>')
// 		{
// 			vars->tokens[vars->i2].out = OUT_REDIRECT;
// 			vars->j2++;
// 			vars->ptr_outfile++;
// 			break ;
// 		}
// 		else
// 		{
// 			vars->j2--;
// 			vars->ptr_outfile--;
// 		}
// 	}
// }

// void	find_outfile_extract_heredoc_outfile(t_prgm *vars)
// {
// 	while (vars->tokens[vars->i2].t_str[vars->j2] == ' ' || \
// 		vars->tokens[vars->i2].t_str[vars->j2] == '\t')
// 	{
// 		vars->j2++;
// 		vars->start_outfile++;
// 	}
// 	while ((vars->tokens[vars->i2].t_str[vars->j2] != ' ' && \
// 		vars->tokens[vars->i2].t_str[vars->j2] != '\0'))
// 	{
// 		vars->j2++;
// 		vars->len_outfile++;
// 	}
// 	vars->tokens[vars->i2].outfile = ft_substr(vars->ptr_outfile, \
// 		vars->start_outfile, vars->len_outfile);
// }

// void	find_outfile_extract_redirection_outfile(t_prgm *vars)
// {
// 	while (vars->tokens[vars->i2].t_str[vars->j2] == ' ' || \
// 		vars->tokens[vars->i2].t_str[vars->j2] == '\t')
// 	{
// 		vars->j2++;
// 		vars->start_outfile++;
// 	}
// 	while ((vars->tokens[vars->i2].t_str[vars->j2] != ' ' && \
// 		vars->tokens[vars->i2].t_str[vars->j2] != '\0'))
// 	{
// 		vars->j2++;
// 		vars->len_outfile++;
// 	}
// 	vars->tokens[vars->i2].outfile = ft_substr(vars->ptr_outfile, \
// 		vars->start_outfile, vars->len_outfile);
// }

// void	find_outfile_extract_outfile(t_prgm *vars)
// {
// 	if (vars->tokens[vars->i2].out != OUT_STD && \
// 		vars->tokens[vars->i2].out == OUT_APPEND)
// 		find_outfile_extract_heredoc_outfile(vars);
// 	else if (vars->tokens[vars->i2].out != OUT_STD && \
// 		vars->tokens[vars->i2].out == OUT_REDIRECT)
// 		find_outfile_extract_redirection_outfile(vars);
// }

int		count_output(t_prgm *vars)
{
	int	j;
	int	nb_output;

	j = 0;
	nb_output = 0;
	while(vars->tokens[vars->i2].t_str[j] != '\0')
	{
		if (vars->tokens[vars->i2].t_str[j] == '>')
			nb_output++;
		if (j > 0)
		{
			if (vars->tokens[vars->i2].t_str[j - 1] == '>' && vars->tokens[vars->i2].t_str[j] == '>')
				nb_output--;
		}
		j++;
	}
	return(nb_output);
}

void	subs_outfile(t_prgm *vars, int *start, int index)
{
	int len_outfile;
	int	j;
	
	len_outfile = 0;
	j = *start;
	skip_white_spaces(vars, start, vars->i2);
	while (vars->tokens[vars->i2].t_str[j] != '\0' && (vars->tokens[vars->i2].t_str[j] != ' ' && vars->tokens[vars->i2].t_str[j] != '\t'))
	{
		len_outfile++;
		j++;
	}
	vars->tokens[vars->i2].outfile[index] = ft_substr(vars->tokens[vars->i2].t_str, *start, len_outfile++);
	*start += len_outfile - 1;
}

void	extract_outfiles(t_prgm *vars)
{
	int	start;
	int	j;
	int	index;
	int	k;

	j = 0;
	index = 0;
	k = 0;
	vars->tokens[vars->i2].nb_output = count_output(vars);
	if (vars->tokens[vars->i2].nb_output > 0)
	{
		vars->tokens[vars->i2].out = malloc(sizeof(int) * (vars->tokens[vars->i2].nb_output + 1));
		vars->tokens[vars->i2].outfile = malloc(sizeof(char *) * (vars->tokens[vars->i2].nb_output + 1));
		vars->tokens[vars->i2].outfile[vars->tokens[vars->i2].nb_output] = NULL;
	}
	while (vars->tokens[vars->i2].t_str[j] != '\0')
	{
		if (j > 0)
		{
			if (vars->tokens[vars->i2].t_str[j] == '>' && vars->tokens[vars->i2].t_str[j - 1] == '>')
			{
				start = j+1;
				vars->tokens[vars->i2].out[index] = OUT_APPEND;
				skip_white_spaces(vars, &start, vars->i2);
				subs_outfile(vars, &start, index);
				index++;
				j = start;
				vars->tokens[vars->i2].cmd[k++] = ' ';
			}
			else if (vars->tokens[vars->i2].t_str[j - 1] == '>')
			{
				start = j;
				vars->tokens[vars->i2].out[index] = OUT_REDIRECT;
				skip_white_spaces(vars, &start, vars->i2);
				subs_outfile(vars, &start, index);
				index++;
				j = start;
				vars->tokens[vars->i2].cmd[k++] = ' ';
			}
			else
			{
				if (vars->tokens[vars->i2].t_str[j] != '>')
					vars->tokens[vars->i2].cmd[k++] = vars->tokens[vars->i2].t_str[j];
				j++;
			}
		}
		else
		{
			if (vars->tokens[vars->i2].t_str[j] != '>')
				vars->tokens[vars->i2].cmd[k++] = vars->tokens[vars->i2].t_str[j];
			j++;
		}
	}
	vars->tokens[vars->i2].cmd[k] = '\0';
}


void	find_outfile(t_prgm *vars)
{
	vars->i2 = 0;
	while (vars->i2 < vars->pipe_ct + 1)
	{
		free(vars->tokens[vars->i2].t_str);
		vars->tokens[vars->i2].t_str = ft_strdup(vars->tokens[vars->i2].cmd);
		free(vars->tokens[vars->i2].cmd);
		vars->tokens[vars->i2].cmd = malloc(sizeof(char) * (ft_strlen(vars->tokens[vars->i2].t_str) + 1));
		find_outfile_init(vars);
		extract_outfiles(vars);
		vars->i2++;
	}
}
