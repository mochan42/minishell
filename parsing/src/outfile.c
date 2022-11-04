/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:41:28 by mochan            #+#    #+#             */
/*   Updated: 2022/11/04 20:42:44 by mochan           ###   ########.fr       */
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
	printf("nb of output =%d\n", vars->tokens[vars->i2].nb_output);
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
				printf("\tvars->tokens[%d].out[%d] =%d\n", vars->i2, index, vars->tokens[vars->i2].out[index]);
				skip_white_spaces(vars, &start, vars->i2);
				subs_outfile(vars, &start, index);
				printf("\tvars->tokens[%d].outfile[%d] :%s\n", vars->i2, index, vars->tokens[vars->i2].outfile[index]);
				index++;
				j = start;
				vars->tokens[vars->i2].cmd[k++] = ' ';
				// printf("\t>> vars->tokens[%d].cmd :%s\n", vars->i2, vars->tokens[vars->i2].cmd);

			}
			else if (vars->tokens[vars->i2].t_str[j - 1] == '>')
			{
				start = j;
				vars->tokens[vars->i2].out[index] = OUT_REDIRECT;
				printf("\tvars->tokens[%d].out[%d] =%d\n", vars->i2, index, vars->tokens[vars->i2].out[index]);
				// printf("HERE\n");
				// exit (0);
				skip_white_spaces(vars, &start, vars->i2);
				subs_outfile(vars, &start, index);
				printf("\tvars->tokens[%d].outfile[%d] :%s\n", vars->i2, index, vars->tokens[vars->i2].outfile[index]);
				index++;
				j = start;
				vars->tokens[vars->i2].cmd[k++] = ' ';
				// printf("\t> vars->tokens[%d].cmd :%s\n", vars->i2, vars->tokens[vars->i2].cmd);
			}
			else
			{
				if (vars->tokens[vars->i2].t_str[j] != '>')
					vars->tokens[vars->i2].cmd[k++] = vars->tokens[vars->i2].t_str[j];
				// printf("\t 1 else vars->tokens[%d].t_str[%d]	:%c\n", vars->i2, j, vars->tokens[vars->i2].t_str[j]);
				j++;
			}
		}
		else
		{
			if (vars->tokens[vars->i2].t_str[j] != '>')
				vars->tokens[vars->i2].cmd[k++] = vars->tokens[vars->i2].t_str[j];
			// printf("2 else vars->tokens[%d].t_str[%d]	:%c\n", vars->i2, j, vars->tokens[vars->i2].t_str[j]);
			j++;
		}
		// printf("j = %d\n", j);
	}
	vars->tokens[vars->i2].cmd[k] = '\0';
	printf("vars->tokens[%d].cmd :%s\n", vars->i2, vars->tokens[vars->i2].cmd);
}


void	find_outfile(t_prgm *vars)
{
	vars->i2 = 0;
	while (vars->i2 < vars->pipe_ct + 1)
	{
		free(vars->tokens[vars->i2].t_str);
		vars->tokens[vars->i2].t_str = ft_strdup(vars->tokens[vars->i2].cmd);
		// printf("OUTFILE : vars->tokens[%d].t_str :%s\n", vars->i2, vars->tokens[vars->i2].t_str);
		free(vars->tokens[vars->i2].cmd);
		vars->tokens[vars->i2].cmd = malloc(sizeof(char) * (ft_strlen(vars->tokens[vars->i2].t_str) + 1));
		find_outfile_init(vars);
		extract_outfiles(vars);
		// find_outfile_go_to_string_end(vars);
		// find_outfile_identify_output_redirection_type(vars);
		// find_outfile_extract_outfile(vars);
		// printf("vars->tokens[%d].outfile :%s\n", vars->i2, \
		// 	vars->tokens[vars->i2].outfile);
		vars->i2++;
	}
}
